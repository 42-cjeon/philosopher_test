/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:26:46 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 17:54:41 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

static enum e_exit_status	exit_with(enum e_exit_status exit_status)
{
	static const char	*err_msg[] = \
	{
		"",
		"Usage : ./philo n_of_philos ttd tte tts [n_of_must_eat]\n",
		"Error : Failed to Dynamic memory alloc\n",
		"Error : Failed to init mutex\n",
		"Error : Runtime Error\n"
	};

	if (exit_status == SUCCESS)
		return (SUCCESS);
	write(2, err_msg[exit_status], ft_strlen(err_msg[exit_status]));
	return (exit_status);
}

int	main(int argc, const char **argv)
{
	t_main_arg		main_arg;
	t_philo_arg		*philo_args;
	t_shared_arg	shared_arg;
	int				result;

	result = SUCCESS;
	if (parse_input(argc, argv, &main_arg))
		return (exit_with(PARSE_FAIL));
	if (alloc_philo_args(main_arg.n_philos, &philo_args))
		return (exit_with(ALLOC_FAIL));
	init_philo_args(&shared_arg, &main_arg, philo_args);
	if (init_mutex(&shared_arg, &main_arg, philo_args))
	{
		free(philo_args);
		return (exit_with(MUTEX_FAIL));
	}
	if (run_simulation(&shared_arg, &main_arg, philo_args))
		result = RUNTIME_FAIL;
	destroy_mutex(&shared_arg, &main_arg, philo_args);
	free(philo_args);
	return (exit_with(result));
}
