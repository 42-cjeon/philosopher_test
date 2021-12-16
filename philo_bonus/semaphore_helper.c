/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 02:03:02 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 17:21:43 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <string.h>
#include "philo.h"

static void	close_semaphore(t_shared_arg *shared_arg)
{
	sem_close(shared_arg->forks);
	sem_close(shared_arg->forks_lock);
	sem_close(shared_arg->is_end_lock);
	sem_close(shared_arg->full_philos);
}

static void	unlink_semaphore(void)
{
	sem_unlink("/ft_forks");
	sem_unlink("/ft_forks_lock");
	sem_unlink("/ft_is_end_lock");
	sem_unlink("/ft_full_philos");
}

static int	open_semaphore(const char *name, unsigned int value, sem_t **target)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, value);
	if (sem == SEM_FAILED)
		return (1);
	*target = sem;
	return (0);
}

void	destroy_semaphore(t_shared_arg *shared_arg)
{
	close_semaphore(shared_arg);
	unlink_semaphore();
}

int	init_semaphore(t_shared_arg *shared_arg, unsigned int n_philos)
{
	int	is_fail;

	memset(shared_arg, 0x00, sizeof(t_shared_arg));
	is_fail = 0;
	is_fail |= open_semaphore("/ft_forks", \
		n_philos, &(shared_arg->forks));
	is_fail |= open_semaphore("/ft_forks_lock", \
		n_philos / 2, &(shared_arg->forks_lock));
	is_fail |= open_semaphore("/ft_is_end_lock", \
		1, &(shared_arg->is_end_lock));
	is_fail |= open_semaphore("/ft_full_philos", \
		0, &(shared_arg->full_philos));
	if (is_fail)
		destroy_semaphore(shared_arg);
	return (is_fail);
}
