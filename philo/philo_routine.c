/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:18:01 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/04 16:38:07 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	handle_think(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stopped)
		return (pthread_mutex_unlock(&data->stop_mutex), 1);
	print_handler(philo, THINK);
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}

short	handle_sleep(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stopped)
		return (pthread_mutex_unlock(&data->stop_mutex), 1);
	print_handler(philo, SLEEP);
	pthread_mutex_unlock(&data->stop_mutex);
	ft_usleep(data->time_to_sleep);
	return (0);
}

short	handle_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stopped)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	print_handler(philo, FORK);
	pthread_mutex_unlock(&data->stop_mutex);
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stopped)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	print_handler(philo, FORK);
	print_handler(philo, EAT);
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}