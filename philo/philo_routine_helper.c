/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:51:44 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/14 17:11:19 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

static void	take_left_fork_first(t_philo_arg *arg)
{
	pthread_mutex_lock(arg->lfork);
	syncronized_log(arg, "has taken a fork");
	pthread_mutex_lock(arg->rfork);
	syncronized_log(arg, "has taken a fork");
}

static void	take_right_fork_first(t_philo_arg *arg)
{
	pthread_mutex_lock(arg->rfork);
	syncronized_log(arg, "has taken a fork");
	pthread_mutex_lock(arg->lfork);
	syncronized_log(arg, "has taken a fork");
}

void	philo_take_forks(t_philo_arg *arg)
{
	if (arg->id % 2 == 0)
		take_left_fork_first(arg);
	else
		take_right_fork_first(arg);
}

void	philo_release_forks(t_philo_arg *arg)
{
	pthread_mutex_unlock(arg->lfork);
	pthread_mutex_unlock(arg->rfork);
}
