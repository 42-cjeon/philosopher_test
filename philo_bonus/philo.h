/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 02:27:24 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/16 18:07:16 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>

# define EPSILON 1000

typedef unsigned long long	t_timestamp;
typedef struct s_shared_arg
{
	sem_t	*forks;
	sem_t	*forks_lock;
	sem_t	*is_end_lock;
	sem_t	*full_philos;
}							t_shared_arg;
typedef struct s_philo_arg
{
	unsigned int	id;
	unsigned int	n_eat;
	t_timestamp		last_eat;
	t_timestamp		started_at;
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
typedef struct s_observer_arg
{
	unsigned int	n_philos;
	pid_t			last_philo;
	sem_t			*full_philos;
	sem_t			*is_end_lock;
}							t_observer_arg;

enum e_exit_status
{
	SUCCESS,
	PARSE_FAIL,
	SEMAPHORE_FAIL,
	RUNTIME_FAIL
};

void		*everyone_full_start(void *_arg);
int			parse_input(int argc, const char **argv, t_main_arg *main_arg);
void		philo_release_forks(t_shared_arg *shared_arg);
void		philo_take_forks(t_shared_arg *shared_arg, t_philo_arg *philo_arg);
int			philo_start(t_shared_arg *shared_arg, t_main_arg *main_arg, \
							t_philo_arg *philo_arg);
int			is_philo_dead(t_shared_arg *shared_arg, t_main_arg *main_arg, \
							t_philo_arg *philo_arg);
void		destroy_semaphore(t_shared_arg *shared_arg);
int			init_semaphore(t_shared_arg *shared_arg, unsigned int n_philos);
int			run_simulation(t_shared_arg *shared_arg, t_main_arg *main_arg, \
								t_philo_arg *philo_arg);
t_timestamp	get_timestamp_in_ms(void);
void		syncronized_log(t_shared_arg *shared_arg, t_philo_arg *philo_arg, \
								const char *msg);
int			smart_sleep(t_shared_arg *shared_arg, t_main_arg *main_arg, \
							t_philo_arg *philo_arg, unsigned long long t);
size_t		ft_strlen(const char *s);

#endif