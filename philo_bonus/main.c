/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:26:46 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 16:33:16 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_shared_arg	shared_arg;
	t_main_arg		main_arg;
	t_philo_arg		philo_arg;
	int				result;

	if (parse_input(argc, argv, &main_arg))
		return (1);
	if (init_semaphore(&shared_arg, main_arg.n_philos))
		return (1);
	result = run_simulation(&shared_arg, &main_arg, &philo_arg);
	destroy_semaphore(&shared_arg);
	return (result);
}
