/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:26:46 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/14 02:22:43 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

int	main(int argc, const char **argv)
{
	t_main_arg		main_arg;
	t_philo_arg		*philo_args;
	t_shared_arg	shared_arg;
	int				result;

	if (parse_input(argc, argv, &main_arg))
		return (1);
	if (alloc_philo_args(main_arg.n_philos, &philo_args))
		return (1);
	philo_args[1].id = 10;
	init_philo_args(&shared_arg, &main_arg, philo_args);
	if (init_mutex(&shared_arg, &main_arg, philo_args))
	{
		free(philo_args);
		return (1);
	}
	result = run_simulation(&shared_arg, &main_arg, philo_args);
	destroy_mutex(&shared_arg, &main_arg, philo_args);
	free(philo_args);
	return (result);
}
