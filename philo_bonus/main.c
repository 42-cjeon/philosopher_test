/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:26:46 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 18:11:32 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

static enum e_exit_status	exit_with(enum e_exit_status exit_status)
{
	static const char	*err_msg[] = \
	{
		"",
		"Usage : ./philo_bonus n_of_philos ttd tte tts [n_of_must_eat]\n",
		"Error : Failed to init semaphore\n",
		"Error : Runtime Error\n"
	};

	if (exit_status == SUCCESS)
		return (SUCCESS);
	write(2, err_msg[exit_status], ft_strlen(err_msg[exit_status]));
	return (exit_status);
}

int	main(int argc, const char **argv)
{
	t_shared_arg	shared_arg;
	t_main_arg		main_arg;
	t_philo_arg		philo_arg;
	int				result;

	result = SUCCESS;
	if (parse_input(argc, argv, &main_arg))
		return (exit_with(PARSE_FAIL));
	if (init_semaphore(&shared_arg, main_arg.n_philos))
		return (exit_with(SEMAPHORE_FAIL));
	if (run_simulation(&shared_arg, &main_arg, &philo_arg))
		result = RUNTIME_FAIL;
	destroy_semaphore(&shared_arg);
	return (exit_with(result));
}
