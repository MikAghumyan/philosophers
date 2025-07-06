/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:18:01 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/07 00:04:20 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
short	handle_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eat = get_currtime();
	philo->eat_counter++;
	if (data->eats_num > 0 && philo->eat_counter >= (size_t)data->eats_num)
		philo->ended = true;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stopped)
		return (pthread_mutex_unlock(&data->stop_mutex), 1);
	print_handler(philo, EAT);
	pthread_mutex_unlock(&data->stop_mutex);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	if (philo->ended)
		return (1);
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
	if (philo->fork1 == philo->fork2)
		return (handle_one_philo(philo, data));
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stopped)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	print_handler(philo, FORK);
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}

short	handle_one_philo(t_philo *philo, t_data *data)
{
	while (true)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stopped)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			pthread_mutex_unlock(philo->fork1);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
	}
	return (1);
}