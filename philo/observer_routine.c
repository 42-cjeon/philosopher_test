/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:09:39 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/14 02:41:48 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

int	observer_is_end(t_observer_arg *arg)
{
	unsigned int	i;
	int				everyone_full;
	int				somone_dead;

	everyone_full = arg->main_arg->option_arg;
	somone_dead = 0;
	i = 0;
	while (i < arg->main_arg->n_philos && !somone_dead)
	{
		pthread_mutex_lock(&(arg->philo_args[i].event_lock));
		everyone_full &= (arg->main_arg->n_eat <= arg->philo_args[i].n_eat);
		somone_dead |= (get_timestamp_in_ms() - \
							arg->philo_args[i].last_eat > arg->main_arg->ttd);
		pthread_mutex_unlock(&(arg->philo_args[i].event_lock));
		if (somone_dead)
		{
			pthread_mutex_lock(&(arg->shared_arg->is_end_lock));
			printf("%llu %u is dead\n", get_timestamp_in_ms() - \
					arg->philo_args[i].started_at, i + 1);
			arg->shared_arg->is_end = 1;
			pthread_mutex_unlock(&(arg->shared_arg->is_end_lock));
		}
		i++;
	}
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
