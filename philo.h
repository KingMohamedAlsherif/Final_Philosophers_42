/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:47:09 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/27 13:14:33 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
#include <limits.h>

typedef struct s_config
{
	int				total_philos;
	size_t			time_to_starve;
	size_t			time_to_consume;
	size_t			time_to_sleep;
	int				meal_quota;
}					t_config;

typedef struct s_philo
{
	int				number;
	pthread_t		life_thread;
	t_config		*settings;

	int				consuming;
	int				meals_consumed;
	size_t			last_feeding;
	size_t			begin_time;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	int				*end_flag;
	pthread_mutex_t	*life_lock;
	pthread_mutex_t	*food_lock;
	pthread_mutex_t	*display_lock;
}					t_philo;

typedef struct s_simulation
{
	t_config		config;
	pthread_t		monitor_thread;
	t_philo			philos[200];
	pthread_mutex_t	fork[200];

	int				end_flag;
	pthread_mutex_t	life_lock;
	pthread_mutex_t	food_lock;
	pthread_mutex_t	display_lock;
}					t_simulation;

int		process_arguments(int count, char **values, t_config *config);
int		setup_simulation(t_simulation *sim);
int		start_philo_threads(t_philo *philos);
int		start_monitor_thread(t_simulation *sim);
int		wait_philo_threads(t_philo *philos);
int		wait_monitor_thread(pthread_t monitor);
void	*life_cycle(void *data);
void	*monitor(void *data);
int		cleanup_locks(t_simulation *sim);
int		is_number(const char *text);
void	write_string(char *text, int output);
long	convert_to_number(const char *text);
size_t	current_timestamp(void);
int		delay_execution(size_t duration);
int		philos_alive(t_philo *philo);
void	display_status(t_philo *philo, char *status);
// int		check_max_min(char *str);
// int		check_philo_args(char **av);
// static int	is_space(char c);
// const char	*valid_input(const char *str);
// void		erroring(char *str);


#endif
