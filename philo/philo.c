/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/03 21:19:30 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	initialize_forks(t_data *data, t_philo *philo)
{
	if (philo->philo_id % 2)
	{
		philo->fork1 = &data->mutexes[(philo->philo_id + data->philos_num - 1)
			% data->philos_num];
		philo->fork2 = &data->mutexes[data->philos_num];
	}
	else
	{
		philo->fork1 = &data->mutexes[data->philos_num];
		philo->fork2 = &data->mutexes[(philo->philo_id + data->philos_num - 1)
			% data->philos_num];
	}
	return (0);
}

short	initialize_threads(t_data *data, t_philo **philos)
{
	size_t	i;

	i = -1;
	while (++i < data->philos_num)
	{
		(*philos)[i].data = data;
		(*philos)[i].philo_id = i;
		initialize_forks(data, (*philos + i));
		pthread_create(&data->threads[i], NULL, start_philo, (*philos + i));
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
	print_handler(philo, THINK);
	pthread_mutex_lock(philo->fork1);
	print_handler(philo, FORK);
	pthread_mutex_lock(philo->fork2);
	print_handler(philo, FORK);
	return (0);
}
