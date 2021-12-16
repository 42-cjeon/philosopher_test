/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:51:39 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 17:55:22 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

void	syncronized_log(t_philo_arg *arg, const char *msg)
{
	pthread_mutex_lock(arg->is_end_lock);
	if (!(*(arg->is_end)))
		printf("%llu %u %s\n", get_timestamp_in_ms() - \
				arg->started_at, arg->id, msg);
	pthread_mutex_unlock(arg->is_end_lock);
}

void	smart_sleep(unsigned long long t)
{
	t_timestamp	sleep_start;

	sleep_start = get_timestamp_in_ms();
	while (get_timestamp_in_ms() - sleep_start <= t)
		usleep(EPSILON);
}
