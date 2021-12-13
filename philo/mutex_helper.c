/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:03:02 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/14 02:24:29 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

static int	init_mutex_fork_event(pthread_mutex_t *fork, \
									pthread_mutex_t *event_lock)
{
	if (pthread_mutex_init(fork, NULL))
		return (1);
	if (pthread_mutex_init(event_lock, NULL))
	{
		pthread_mutex_destroy(fork);
		return (1);
	}
	return (0);
}

int	init_mutex(t_shared_arg *shared_arg, t_main_arg *main_arg, \
				t_philo_arg *philo_arg)
{
	unsigned int	i;

	if (pthread_mutex_init(&(shared_arg->is_end_lock), NULL))
		return (1);
	i = 0;
	while (i < main_arg->n_philos)
	{
		if (init_mutex_fork_event(&(philo_arg[i]._fork), \
				&(philo_arg[i].event_lock)))
		{
			while (i--)
			{
				pthread_mutex_destroy(&(philo_arg[i]._fork));
				pthread_mutex_destroy(&(philo_arg[i].event_lock));
			}
			pthread_mutex_destroy(&(shared_arg->is_end_lock));
			return (1);
		}
		i++;
	}
	return (0);
}

void	destroy_mutex(t_shared_arg *shared_arg, t_main_arg *main_arg, \
						t_philo_arg *philo_arg)
{
	unsigned int	i;

	pthread_mutex_destroy(&(shared_arg->is_end_lock));
	i = 0;
	while (i < main_arg->n_philos)
	{
		pthread_mutex_destroy(&(philo_arg[i]._fork));
		pthread_mutex_destroy(&(philo_arg[i].event_lock));
		i++;
	}
}
