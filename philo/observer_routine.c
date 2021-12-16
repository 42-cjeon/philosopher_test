/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:09:39 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 12:37:04 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static void	handle_someone_dead(t_philo_arg *arg)
{
	pthread_mutex_lock(arg->is_end_lock);
	printf("%llu %u died\n", get_timestamp_in_ms() - arg->started_at, arg->id);
	*(arg->is_end) = 1;
	philo_release_forks(arg);
	pthread_mutex_unlock(arg->is_end_lock);
}

static void	handle_everyone_full(t_shared_arg *arg)
{
	stop_simulation(arg);
}

int	observer_is_end(t_observer_arg *arg)
{
	unsigned int	i;
	int				everyone_full;
	int				somone_dead;

	everyone_full = arg->main_arg->option_arg;
	i = 0;
	while (i < arg->main_arg->n_philos)
	{
		pthread_mutex_lock(&(arg->philo_args[i].event_lock));
		everyone_full &= (arg->main_arg->n_eat <= arg->philo_args[i].n_eat);
		somone_dead = (get_timestamp_in_ms() - \
							arg->philo_args[i].last_eat > arg->main_arg->ttd);
		pthread_mutex_unlock(&(arg->philo_args[i].event_lock));
		if (somone_dead)
			break ;
		i++;
	}
	if (somone_dead)
		handle_someone_dead(arg->philo_args + i);
	else if (everyone_full)
		handle_everyone_full(arg->shared_arg);
	return (everyone_full || somone_dead);
}

void	*observer_start(void *_arg)
{
	t_observer_arg	*arg;

	arg = (t_observer_arg *)_arg;
	while (42)
	{
		if (observer_is_end(arg))
		{
			stop_simulation(arg->shared_arg);
			return (NULL);
		}
		usleep(EPSILON);
	}
}
