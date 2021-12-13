/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:05:57 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/14 02:35:42 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

static void	join_all(pthread_t *observer, t_philo_arg *philo_arg, \
						unsigned int i)
{
	if (observer != NULL)
		pthread_join(*observer, NULL);
	while (i--)
		pthread_join(philo_arg[i].philo, NULL);
}

static int	abort_simulation(t_shared_arg *shared_arg, \
								t_philo_arg *philo_arg, unsigned int i)
{
	stop_simulation(shared_arg);
	join_all(NULL, philo_arg, i);
	return (1);
}

int	is_simulation_end(t_philo_arg *arg)
{
	int	result;

	pthread_mutex_lock(arg->is_end_lock);
	result = *(arg->is_end);
	pthread_mutex_unlock(arg->is_end_lock);
	return (result);
}

void	stop_simulation(t_shared_arg *shared_arg)
{
	pthread_mutex_lock(&(shared_arg->is_end_lock));
	shared_arg->is_end = 1;
	pthread_mutex_unlock(&(shared_arg->is_end_lock));
}

int	run_simulation(t_shared_arg *shared_arg, t_main_arg *main_arg, \
					t_philo_arg *philo_arg)
{
	unsigned int	i;
	t_timestamp		now;
	pthread_t		observer;

	i = 0;
	while (i < main_arg->n_philos)
	{
		now = get_timestamp_in_ms();
		philo_arg[i].started_at = now;
		philo_arg[i].last_eat = now;
		if (pthread_create(&(philo_arg[i].philo), NULL, philo_start, \
							&philo_arg[i]))
			return (abort_simulation(shared_arg, philo_arg, i));
		i++;
	}
	if (pthread_create(&observer, NULL, observer_start, \
			&(t_observer_arg){shared_arg, main_arg, philo_arg}))
		return (abort_simulation(shared_arg, philo_arg, i));
	join_all(&observer, philo_arg, i);
	return (0);
}
