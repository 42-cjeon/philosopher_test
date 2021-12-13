/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 02:27:24 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/14 02:48:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define EPSILON 1000

typedef unsigned long long	t_timestamp;
typedef struct s_philo_arg
{
	unsigned int	id;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	n_eat;
	t_timestamp		last_eat;
	pthread_mutex_t	event_lock;
	t_timestamp		started_at;
	pthread_t		philo;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	_fork;
	char			*is_end;
	pthread_mutex_t	*is_end_lock;
}							t_philo_arg;
typedef struct s_main_arg
{
	unsigned int	n_philos;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	n_eat;
	unsigned int	option_arg;
}							t_main_arg;
typedef struct s_shared_arg
{
	pthread_mutex_t	is_end_lock;
	char			is_end;
}							t_shared_arg;
typedef struct s_observer_arg
{
	t_shared_arg	*shared_arg;
	t_main_arg		*main_arg;
	t_philo_arg		*philo_args;
}							t_observer_arg;

int			init_mutex(t_shared_arg *shared_arg, t_main_arg *main_arg, \
						t_philo_arg *philo_arg);
void		destroy_mutex(t_shared_arg *shared_arg, t_main_arg *main_arg, \
						t_philo_arg *philo_arg);
void		*observer_start(void *_arg);
int			parse_input(int argc, const char **argv, t_main_arg *main_arg);
int			alloc_philo_args(unsigned int n_philos, t_philo_arg **philo_args);
void		init_philo_args(t_shared_arg *shared_arg, t_main_arg *main_arg, \
								t_philo_arg *philo_arg);
void		philo_take_forks(t_philo_arg *arg);
void		philo_release_forks(t_philo_arg *arg);
void		*philo_start(void *_arg);
int			is_simulation_end(t_philo_arg *arg);
void		stop_simulation(t_shared_arg *shared_arg);
int			run_simulation(t_shared_arg *shared_arg, t_main_arg *main_arg, \
							t_philo_arg *philo_arg);
void		smart_sleep(unsigned long long t);
void		syncronized_log(t_philo_arg *arg, const char *msg);
t_timestamp	get_timestamp_in_ms(void);

#endif