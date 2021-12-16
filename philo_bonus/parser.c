/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:57:32 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 17:17:24 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "philo.h"

static int	ft_isdigit(const char c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_atoll(const char *str, long long *n)
{
	int	len;

	len = 0;
	*n = 0;
	while (ft_isdigit(str[len]))
	{
		if (len > 10)
			break ;
		*n = *n * 10 + (str[len] - '0');
		len++;
	}
	if (str[len] != '\0' || len == 0 || UINT32_MAX < *n || *n <= 0)
		return (1);
	return (0);
}

static int	parse_required(const char **argv, t_main_arg *main_arg)
{
	long long	k;

	if (ft_atoll(argv[1], &k))
		return (1);
	main_arg->n_philos = k;
	if (ft_atoll(argv[2], &k))
		return (1);
	main_arg->ttd = k;
	if (ft_atoll(argv[3], &k))
		return (1);
	main_arg->tte = k;
	if (ft_atoll(argv[4], &k))
		return (1);
	main_arg->tts = k;
	main_arg->option_arg = 0;
	return (0);
}

static int	parse_optional(const char **argv, t_main_arg *main_arg)
{
	long long	k;

	if (parse_required(argv, main_arg))
		return (1);
	if (ft_atoll(argv[5], &k))
		return (1);
	main_arg->n_eat = k;
	main_arg->option_arg = 1;
	return (0);
}

int	parse_input(int argc, const char **argv, t_main_arg *main_arg)
{
	if (argc == 5)
		return (parse_required(argv, main_arg));
	if (argc == 6)
		return (parse_optional(argv, main_arg));
	else
		return (1);
}
