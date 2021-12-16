/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:51:39 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 18:04:23 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

t_timestamp	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	syncronized_log(t_shared_arg *shared_arg, t_philo_arg *philo_arg, \
							const char *msg)
{
	sem_wait(shared_arg->is_end_lock);
	printf("%llu %u %s\n", get_timestamp_in_ms() - \
			philo_arg->started_at, philo_arg->id, msg);
	sem_post(shared_arg->is_end_lock);
}

int	smart_sleep(t_shared_arg *shared_arg, t_main_arg *main_arg, \
					t_philo_arg *philo_arg, unsigned long long t)
{
	t_timestamp	sleep_start;
	t_timestamp	now;

	sleep_start = get_timestamp_in_ms();
	now = sleep_start;
	while (now - sleep_start <= t)
	{
		if (is_philo_dead(shared_arg, main_arg, philo_arg))
			return (1);
		usleep(EPSILON);
		now = get_timestamp_in_ms();
	}
	return (0);
}
