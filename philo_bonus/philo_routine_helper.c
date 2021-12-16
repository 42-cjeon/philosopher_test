/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:51:44 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 17:17:32 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include "philo.h"

void	philo_take_forks(t_shared_arg *shared_arg, t_philo_arg *philo_arg)
{
	sem_wait(shared_arg->forks_lock);
	sem_wait(shared_arg->forks);
	syncronized_log(shared_arg, philo_arg, "has taken a fork");
	sem_wait(shared_arg->forks);
	syncronized_log(shared_arg, philo_arg, "has taken a fork");
}

void	philo_release_forks(t_shared_arg *shared_arg)
{
	sem_post(shared_arg->forks);
	sem_post(shared_arg->forks);
	sem_post(shared_arg->forks_lock);
}
