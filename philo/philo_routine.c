/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:51:42 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/14 02:28:09 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

static int	philo_eat(t_philo_arg *arg)
{
	philo_take_forks(arg);
	pthread_mutex_lock(&(arg->event_lock));
	arg->last_eat = get_timestamp_in_ms();
	pthread_mutex_unlock(&(arg->event_lock));
	syncronized_log(arg, "is eating");
	smart_sleep(arg->tte);
	pthread_mutex_lock(&(arg->event_lock));
	arg->n_eat += 1;
	pthread_mutex_unlock(&(arg->event_lock));
	philo_release_forks(arg);
	return (is_simulation_end(arg));
}

static int	philo_sleep(t_philo_arg *arg)
{
	syncronized_log(arg, "is sleeping");
	smart_sleep(arg->tts);
	return (is_simulation_end(arg));
}

static int	philo_think(t_philo_arg *arg)
{
	syncronized_log(arg, "is thinking");
	return (is_simulation_end(arg));
}

void	*philo_start(void *_arg)
{
	t_philo_arg	*arg;

	arg = (t_philo_arg *)_arg;
	while (42)
	{
		if (philo_eat(arg))
			return (NULL);
		if (philo_sleep(arg))
			return (NULL);
		if (philo_think(arg))
			return (NULL);
	}
}
