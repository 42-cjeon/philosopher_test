#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define EPSILON 1000

typedef unsigned long long t_timestamp;
typedef struct s_philo_arg
{
	t_timestamp sim_start;
	t_timestamp last_eat;
	unsigned int id;
	sem_t *forks;
	sem_t *forks_lock;
	sem_t *is_end_lock;
}	t_philo_arg;

enum e_simulation_state
{
	SIM_END,
	SIM_CONTINUE
};

int ttd = 320;
int tte = 100;
int tts = 200;
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

	if (now - arg->last_eat >= ttd)
	{
		sem_wait(arg->is_end_lock);
		printf("%llu %u is dead\n", now - arg->sim_start, arg->id);
		return 1;
	}
	return (0);
}

int safe_log(t_philo_arg *arg, const char *str)
{
	int result;

	result = 0;
	sem_wait(arg->is_end_lock);
	printf("%llu %u %s\n", get_timestamp_in_ms() - arg->sim_start, arg->id, str);
	sem_post(arg->is_end_lock);
	return result;
}

void release_fork(t_philo_arg *arg)
{
	sem_post(arg->forks);
	sem_post(arg->forks);
	sem_post(arg->forks_lock);
}

int philo_eat(t_philo_arg *arg)
{
	t_timestamp eat_started_at;
	int result;

	eat_started_at = get_timestamp_in_ms();
	arg->last_eat = eat_started_at;
	if (is_philo_dead(arg, get_timestamp_in_ms()))
		result = SIM_END;
	else
	{
		safe_log(arg, "is eating");
		while (42)
		{
			if (get_timestamp_in_ms() - eat_started_at >= tte)
			{
				result = SIM_CONTINUE;
				break ;
			}
			usleep(EPSILON);
		}
	}
	release_fork(arg);
	return result;
}

void take_fork(t_philo_arg *arg)
{
	sem_wait(arg->forks_lock);
	sem_wait(arg->forks);
	safe_log(arg, "is taken fork");
	sem_wait(arg->forks);
	safe_log(arg, "is taken fork");
}

int philo_think(t_philo_arg *arg)
{
	if (is_philo_dead(arg, get_timestamp_in_ms()))
		return (SIM_END);
	safe_log(arg, "is thinking");
	take_fork(arg);
	return (SIM_CONTINUE);
}

int philo_sleep(t_philo_arg *arg)
{
	t_timestamp sleep_started_at;

	safe_log(arg, "is sleeping");
	sleep_started_at = get_timestamp_in_ms();
	while (42)
	{
		if (is_philo_dead(arg, get_timestamp_in_ms()))
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
		if (philo_think(arg) == SIM_END)
			return (NULL);
		if (philo_eat(arg) == SIM_END)
			return (NULL);
		if (philo_sleep(arg) == SIM_END)
			return (NULL);
	}
}

int main(void)
{
	pid_t *philos;
	pid_t current_pid;
	sem_t *forks;
	sem_t *forks_lock;
	sem_t *is_end_lock;
	t_philo_arg philo_args;
	t_timestamp started_at;
	int is_end;
	int status;

	sem_unlink("forks");
	sem_unlink("forks_lock");
	sem_unlink("is_end_lock");

	forks = sem_open("forks", O_CREAT , S_IRUSR | S_IWUSR, n_philo);
	forks_lock = sem_open("forks_lock", O_CREAT, S_IRUSR | S_IWUSR , n_philo / 2);
	is_end_lock = sem_open("is_end_lock", O_CREAT, S_IRUSR | S_IWUSR, 1);
	philos = (pid_t *)malloc(sizeof(pid_t) * n_philo);
	philo_args.forks = forks;
	philo_args.forks_lock = forks_lock;
	philo_args.is_end_lock = is_end_lock;
	philo_args.sim_start = get_timestamp_in_ms();
	philo_args.last_eat = philo_args.sim_start;
	for (int i = 0; i < n_philo; i++)
	{
		current_pid = fork();
		if (current_pid == 0)
		{
			philo_args.id = i;
			//printf("|%p|\n", forks);
			//exit(0);
			philo(&philo_args);
			exit(0);
		}
		else
			philos[i] = current_pid;
	}
	//rintf("%llums", get_timestamp_in_ms() - s);
	waitpid(-1, &status, 0);
	for (int i = 0; i < n_philo; i++)
		kill(philos[i], SIGSTOP);
	free(philos);
	sem_close(forks); sem_unlink("forks");
	sem_close(forks_lock); sem_unlink("forks_lock");
	sem_close(is_end_lock); sem_unlink("is_end_lock");

	return (0);
}

/*
int main(void)
{
	stm_t forks
	pid_t pids[10];
	pid_t current_pid;
	int status;
	//sem = sem_open("forks", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 10);
	for (int i = 0; i < 10; i++)
	{
		current_pid = fork();
		if (current_pid == 0)
		{
			philo();
			exit(0);
		}
		pids[i] = current_pid;
	}
	for (int i = 0; i < 10; i++)
		waitpid(pids[i], &status, 0);
	return 0;
}
*/