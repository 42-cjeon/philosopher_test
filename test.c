#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define EPSILON 1000
#define US_PER_MS 1000

typedef int t_fork;
typedef unsigned long long t_timestamp;
typedef struct s_philo_arg
{
	t_timestamp last_eat;
	unsigned int id;
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	pthread_mutex_t *is_end_lock;
	int *is_end;
}	t_philo_arg;

enum e_simulation_state
{
	SIM_END,
	SIM_CONTINUE
};

int ttd = 600;
int tte = 100;
int tts = 100;
int n_philo = 200;

t_timestamp get_timestamp_in_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
int is_philo_dead(t_philo_arg *arg, t_timestamp now)
{
	int result;

	result = 0;
	pthread_mutex_lock(arg->is_end_lock);
	if (now - arg->last_eat >= ttd)
	{
		printf("%llu %u is dead\n", now, arg->id);
		*(arg->is_end) = 1;
		result = 1;
	}
	pthread_mutex_unlock(arg->is_end_lock);
	return (result);
}
int is_somone_dead(t_philo_arg *arg)
{
	int result;

	result = 0;
	pthread_mutex_lock(arg->is_end_lock);
	if (*(arg->is_end))
		result = 1;
	pthread_mutex_unlock(arg->is_end_lock);
	return (result);
}
int philo_eat(t_philo_arg *arg)
{
	t_timestamp eat_started_at;
	int result;

	if (is_philo_dead(arg, get_timestamp_in_ms()) || is_somone_dead(arg))
		result = SIM_END;
	else
	{
		eat_started_at = get_timestamp_in_ms();
		arg->last_eat = eat_started_at;
		printf("%llu %u is eating\n", eat_started_at, arg->id);
		while (42)
		{
			if (is_somone_dead(arg))
			{
				result = SIM_END;
				break ;
			}
			if (get_timestamp_in_ms() - eat_started_at >= tte)
			{
				result = SIM_CONTINUE;
				break ;
			}
			usleep(EPSILON);
		}
	}
	pthread_mutex_unlock(arg->lfork);
	pthread_mutex_unlock(arg->rfork);
	return result;
}

int philo_think(t_philo_arg *arg)
{
	if (is_philo_dead(arg, get_timestamp_in_ms()) || is_somone_dead(arg))
		return (SIM_END);
	printf("%llu %u is thinking\n", get_timestamp_in_ms(), arg->id);
	if (arg->id % 2 == 0)
	{
		pthread_mutex_lock(arg->lfork);
		pthread_mutex_lock(arg->rfork);
	}
	else
	{
		pthread_mutex_lock(arg->rfork);
		pthread_mutex_lock(arg->lfork);
	}
	return (SIM_CONTINUE);
}

int philo_sleep(t_philo_arg *arg)
{
	t_timestamp sleep_started_at;

	if (is_philo_dead(arg, get_timestamp_in_ms()) || is_somone_dead(arg))
		return (SIM_END);
	printf("%llu %u is sleeping\n", get_timestamp_in_ms(), arg->id);
	sleep_started_at = get_timestamp_in_ms();
	while (42)
	{
		if (is_philo_dead(arg, get_timestamp_in_ms()) || is_somone_dead(arg))
			return (SIM_END);
		if (get_timestamp_in_ms() - sleep_started_at >= tts)
			break ;
		usleep(EPSILON);
	}
	return (SIM_CONTINUE);
}
void *philo(void *_arg)
{
	t_philo_arg *arg;

	arg = (t_philo_arg *)_arg;
	while (42)
	{
		if (philo_eat(arg) == SIM_END)
			return (NULL);
		if (philo_sleep(arg) == SIM_END)
			return (NULL);
		if (philo_think(arg) == SIM_END)
			return (NULL);
	}
}

int main(void)
{
	pthread_t *philos;
	pthread_mutex_t *forks;
	t_philo_arg *philo_args;
	pthread_mutex_t is_end_lock;
	int is_end;

	is_end = 0;
	philos = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_philo);
	philo_args = (t_philo_arg *)malloc(sizeof(t_philo_arg) * n_philo);

	for (int i = 0; i < n_philo; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&is_end_lock, NULL);
	}
	for (int i = 0; i < n_philo; i++)
	{
		philo_args[i].id = i + 1;
		philo_args[i].is_end = &is_end;
		philo_args[i].is_end_lock = &is_end_lock;
		philo_args[i].lfork = &forks[i];
		philo_args[i].rfork = &forks[(i + 1) % n_philo];
		philo_args[i].last_eat = get_timestamp_in_ms();
		pthread_create(philos + i, NULL, philo, philo_args + i);
	}
	for (int i = 0; i < n_philo; i++)
		pthread_join(philos[i], NULL);
	free(philos);
	free(forks);
	free(philo_args);
	return (0);
}