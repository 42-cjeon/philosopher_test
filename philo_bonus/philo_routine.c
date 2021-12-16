/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:51:42 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 18:17:24 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdio.h>
#include "philo.h"

static int	philo_eat(t_shared_arg *shared_arg, t_main_arg *main_arg, \
						t_philo_arg *philo_arg)
{
	philo_take_forks(shared_arg, philo_arg);
	philo_arg->last_eat = get_timestamp_in_ms();
	syncronized_log(shared_arg, philo_arg, "is eating");
	if (smart_sleep(shared_arg, main_arg, philo_arg, main_arg->tte))
		return (1);
	if (++(philo_arg->n_eat) == main_arg->n_eat)
		sem_post(shared_arg->full_philos);
	philo_release_forks(shared_arg);
	return (0);
}

static int	philo_sleep(t_shared_arg *shared_arg, t_main_arg *main_arg, \
							t_philo_arg *philo_arg)
{
	syncronized_log(shared_arg, philo_arg, "is sleeping");
	if (smart_sleep(shared_arg, main_arg, philo_arg, main_arg->tts))
		return (1);
	return (0);
}

static int	philo_think(t_shared_arg *shared_arg, t_philo_arg *philo_arg)
{
	syncronized_log(shared_arg, philo_arg, "is thinking");
	return (0);
}

int	is_philo_dead(t_shared_arg *shared_arg, t_main_arg *main_arg, \
					t_philo_arg *philo_arg)
{
	int	is_dead;

	is_dead = (get_timestamp_in_ms() - philo_arg->last_eat > main_arg->ttd);
	if (is_dead)
	{
		sem_wait(shared_arg->is_end_lock);
		printf("%llu %u died\n", \
			get_timestamp_in_ms() - philo_arg->started_at, philo_arg->id);
	}
	return (is_dead);
}

int	philo_start(t_shared_arg *shared_arg, t_main_arg *main_arg, \
					t_philo_arg *philo_arg)
{
	if (main_arg->n_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		return (smart_sleep(shared_arg, main_arg, \
					philo_arg, main_arg->ttd * 2));
	}
	while (42)
	{
		if (is_philo_dead(shared_arg, main_arg, philo_arg) \
			|| philo_eat(shared_arg, main_arg, philo_arg))
			return (0);
		if (is_philo_dead(shared_arg, main_arg, philo_arg) \
			|| philo_sleep(shared_arg, main_arg, philo_arg))
			return (0);
		if (is_philo_dead(shared_arg, main_arg, philo_arg) \
			|| philo_think(shared_arg, philo_arg))
			return (0);
	}
}
