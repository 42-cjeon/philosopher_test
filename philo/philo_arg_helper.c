/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_arg_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:03:00 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/14 02:42:03 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

int	alloc_philo_args(unsigned int n_philos, t_philo_arg **philo_args)
{
	*philo_args = (t_philo_arg *)malloc(sizeof(t_philo_arg) * n_philos);
	return (*philo_args == NULL);
}

void	init_philo_args(t_shared_arg *shared_arg, t_main_arg *main_arg, \
							t_philo_arg *philo_arg)
{
	unsigned int	i;

	shared_arg->is_end = 0;
	i = 0;
	while (i < main_arg->n_philos)
	{
		philo_arg[i].id = i + 1;
		philo_arg[i].n_eat = 0;
		philo_arg[i].is_end = &(shared_arg->is_end);
		philo_arg[i].is_end_lock = &(shared_arg->is_end_lock);
		philo_arg[i].lfork = &(philo_arg[i]._fork);
		philo_arg[i].rfork = &(philo_arg[(i + 1) % main_arg->n_philos]._fork);
		philo_arg[i].tte = main_arg->tte;
		philo_arg[i].tts = main_arg->tts;
		i++;
	}
}
