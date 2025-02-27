/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mintor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:46:37 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/26 09:46:38 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philo_starved(t_philo *philo)
{
	size_t	elapsed;

	pthread_mutex_lock(philo->food_lock);
	elapsed = current_timestamp() - philo->last_feeding;
	if (elapsed > philo->settings->time_to_starve && !philo->consuming)
	{
		pthread_mutex_unlock(philo->food_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->food_lock);
	return (0);
}

static int	check_starvation(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->settings->total_philos)
	{
		if (is_philo_starved(&philos[i]))
		{
			display_status(&philos[i], "starved");
			pthread_mutex_lock(philos->life_lock);
			*philos->end_flag = 1;
			pthread_mutex_unlock(philos->life_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	meal_quota_reached(t_philo *philos)
{
	int	i;

	if (philos->settings->meal_quota == -1)
		return (0);
	i = 0;
	while (i < philos->settings->total_philos)
	{
		pthread_mutex_lock(philos->food_lock);
		if (philos[i].meals_consumed < philos->settings->meal_quota)
		{
			pthread_mutex_unlock(philos->food_lock);
			return (0);
		}
		pthread_mutex_unlock(philos->food_lock);
		i++;
	}
	pthread_mutex_lock(philos->life_lock);
	*philos->end_flag = 1;
	pthread_mutex_unlock(philos->life_lock);
	return (1);
}

void	*monitor(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	while (1)
	{
		if (check_starvation(philos) || meal_quota_reached(philos))
			break ;
	}
	return (data);
}
