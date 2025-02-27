/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:45:36 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/27 13:22:30 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->life_lock);
	if (*philo->end_flag == 1)
	{
		pthread_mutex_unlock(philo->life_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->life_lock);
	return (1);
}

void	display_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->display_lock);
	if (philos_alive(philo))
	{
		printf("%zu %d %s\n", current_timestamp() - philo->begin_time,
			philo->number, status);
	}
	pthread_mutex_unlock(philo->display_lock);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (process_arguments(argc, argv, &sim.config) != 0)
		return (1);
	if (setup_simulation(&sim) != 0)
		return (1);
	if (start_monitor_thread(&sim) != 0 || start_philo_threads(sim.philos) != 0)
	{
		cleanup_locks(&sim);
		return (1);
	}
	if (wait_monitor_thread(sim.monitor_thread) != 0 ||
		wait_philo_threads(sim.philos) != 0)
	{
		cleanup_locks(&sim);
		return (1);
	}
	cleanup_locks(&sim);
	return (0);
}

int	cleanup_locks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.total_philos)
	{
		if (pthread_mutex_destroy(&sim->fork[i]) != 0)
		{
			write_string("Error: fork lock cleanup failed\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_destroy(&sim->life_lock) != 0 ||
		pthread_mutex_destroy(&sim->food_lock) != 0 ||
		pthread_mutex_destroy(&sim->display_lock) != 0)
	{
		write_string("Error: Lock cleanup failed\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
