/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:47:13 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/27 13:15:29 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	prepare_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			write_string("Error: fork lock init failed\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	configure_philos(t_simulation *sim)
{
	int				i;
	t_philo		*philos;
	pthread_mutex_t	*forks;
	t_config		*config;

	i = 0;
	philos = sim->philos;
	forks = sim->fork;
	config = &sim->config;
	while (i < config->total_philos)
	{
		philos[i].number = i + 1;
		philos[i].settings = config;
		philos[i].consuming = 0;
		philos[i].meals_consumed = 0;
		philos[i].last_feeding = current_timestamp();
		philos[i].begin_time = current_timestamp();
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % config->total_philos];
		philos[i].end_flag = &sim->end_flag;
		philos[i].life_lock = &sim->life_lock;
		philos[i].food_lock = &sim->food_lock;
		philos[i].display_lock = &sim->display_lock;
		i++;
	}
}

int	setup_simulation(t_simulation *sim)
{
	if (prepare_forks(sim->fork, sim->config.total_philos) != 0)
		return (1);
	sim->end_flag = 0;
	if (pthread_mutex_init(&sim->life_lock, NULL) != 0 ||
		pthread_mutex_init(&sim->food_lock, NULL) != 0 ||
		pthread_mutex_init(&sim->display_lock, NULL) != 0)
	{
		write_string("Error: Lock init failed\n", STDERR_FILENO);
		return (1);
	}
	configure_philos(sim);
	return (0);
}
static void	think_eat_rest(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display_status(philo, "picked up a fork");
	if (philo->settings->total_philos == 1)
	{
		delay_execution(philo->settings->time_to_starve);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	display_status(philo, "picked up a fork");
	display_status(philo, "is eating");
	philo->consuming = 1;
	pthread_mutex_lock(philo->food_lock);
	philo->last_feeding = current_timestamp();
	philo->meals_consumed++;
	pthread_mutex_unlock(philo->food_lock);
	delay_execution(philo->settings->time_to_consume);
	philo->consuming = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	display_status(philo, "is resting");
	delay_execution(philo->settings->time_to_sleep);
	display_status(philo, "is thinking");
}


void	*life_cycle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->number % 2 == 0)
		delay_execution(philo->settings->time_to_consume);
	while (philos_alive(philo))
	{
		think_eat_rest(philo);
		if (philo->settings->total_philos == 1)
			break ;
	}
	return (data);
}