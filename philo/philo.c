/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/05 15:57:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	join_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philos_num)
		pthread_join(data->threads[i++], NULL);
	return (0);
}

short	monitor_routine(t_data *data, t_philo **philos)
{
	size_t	i;
	size_t	count_ended;

	while (!data->stopped)
	{
		i = -1;
		count_ended = 0;
		while (++i < data->philos_num)
		{
			pthread_mutex_lock(&(*philos)[i].meal_mutex);
			if ((*philos)[i].ended)
				count_ended++;
			else if (get_currtime() - (*philos)[i].last_eat > data->time_to_die)
			{
				pthread_mutex_lock(&data->stop_mutex);
				if (data->stopped)
					break ;
				data->stopped = true;
				print_handler((*philos + i), DIED);
				pthread_mutex_unlock(&data->stop_mutex);
				pthread_mutex_unlock(&(*philos)[i].meal_mutex);
				break ;
			}
			pthread_mutex_unlock(&(*philos)[i].meal_mutex);
		}
		if (count_ended == data->philos_num)
			break ;
	}
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
