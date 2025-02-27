/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:47:20 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/26 09:47:24 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_philo_threads(t_philo *philos)
{
    int i;
    int total = philos->settings->total_philos;

    i = 0;
    while (i < total)
    {
        if (pthread_create(&philos[i].life_thread, NULL, life_cycle, &philos[i]) != 0)
        {
            write_string("Error: Failed to create philo thread\n", STDERR_FILENO);
            return (1);
        }
        i++;
    }
    return (0);
}

int start_monitor_thread(t_simulation *sim)
{
    if (pthread_create(&sim->monitor_thread, NULL, monitor, sim->philos) != 0)
    {
        write_string("Error: Failed to create monitor thread\n", STDERR_FILENO);
        return (1);
    }
    return (0);
}

int wait_philo_threads(t_philo *philos)
{
    int i;
    int total = philos->settings->total_philos;

    i = 0;
    while (i < total)
    {
        if (pthread_join(philos[i].life_thread, NULL) != 0)
        {
            write_string("Error: Failed to join philo thread\n", STDERR_FILENO);
            return (1);
        }
        i++;
    }
    return (0);
}

int wait_monitor_thread(pthread_t monitor)
{
    if (pthread_join(monitor, NULL) != 0)
    {
        write_string("Error: Failed to join monitor thread\n", STDERR_FILENO);
        return (1);
    }
    return (0);
}
