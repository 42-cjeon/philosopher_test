/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:09:39 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 17:30:47 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <signal.h>
#include "philo.h"

#include <stdio.h>

void	*everyone_full_start(void *_arg)
{
	unsigned int	i;
	t_observer_arg	*arg;

	arg = (t_observer_arg *)_arg;
	i = 0;
	while (i < arg->n_philos)
	{
		sem_wait(arg->full_philos);
		i++;
	}
	sem_wait(arg->is_end_lock);
	kill(arg->last_philo, SIGTERM);
	return (NULL);
}
