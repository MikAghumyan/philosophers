/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/07 00:04:20 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	check_philo_dead(t_philo *philo, t_data *data, size_t *count_ended)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->ended)
		(*count_ended)++;
	else if (get_currtime() - philo->last_eat > data->time_to_die)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (!data->stopped)
		{
			data->stopped = true;
			print_handler(philo, DIED);
		}
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (false);
}

short	monitor_routine(t_data *data, t_philo **philos)
{
	size_t	i;
	size_t	count_ended;
	bool	stopped;

	while (true)
	{
		pthread_mutex_lock(&data->stop_mutex);
		stopped = data->stopped;
		pthread_mutex_unlock(&data->stop_mutex);
		if (stopped)
			break ;
		i = -1;
		count_ended = 0;
		while (++i < data->philos_num)
		{
			if (check_philo_dead((*philos + i), data, &count_ended))
				return (0);
		}
		if (count_ended == data->philos_num)
			break ;
		usleep(500);
	}
	return (0);
}

short	join_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philos_num)
		pthread_join(data->threads[i++], NULL);
	return (0);
}

void	*start_philo(void *args)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)args;
	data = philo->data;
	while (true)
	{
		if (handle_think(philo, data))
			break ;
		if (handle_forks(philo, data))
			break ;
		if (handle_eat(philo, data))
			break ;
		if (handle_sleep(philo, data))
			break ;
	}
	return (0);
}
