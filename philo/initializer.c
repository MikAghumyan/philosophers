/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:42:49 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/04 13:52:58 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	initialize_forks(t_data *data, t_philo *philo)
{
	size_t	prev_fork;
	size_t	next_fork;

	prev_fork = (philo->philo_id + data->philos_num - 1) % data->philos_num;
	next_fork = philo->philo_id;
	if (philo->philo_id % 2)
	{
		philo->fork1 = &data->mutexes[prev_fork];
		philo->fork2 = &data->mutexes[next_fork];
	}
	else
	{
		philo->fork1 = &data->mutexes[next_fork];
		philo->fork2 = &data->mutexes[prev_fork];
	}
	return (0);
}

short	initialize_threads(t_data *data, t_philo **philos)
{
	size_t	i;

	data->start_time = get_currtime();
	i = -1;
	while (++i < data->philos_num)
	{
		(*philos)[i].data = data;
		(*philos)[i].philo_id = i;
		(*philos)[i].eat_counter = 0;
		(*philos)[i].last_eat = get_currtime();
		(*philos)[i].ended = false;
		if (pthread_mutex_init(&((*philos)[i].meal_mutex), NULL))
			return (-1);
		initialize_forks(data, (*philos + i));
		pthread_create(&data->threads[i], NULL, start_philo, (*philos + i));
	}
	return (0);
}

short	initialize_mutexes(t_data *data)
{
	size_t	i;

	i = -1;
	data->mutex_count = 0;
	while (++i < data->philos_num)
	{
		if (pthread_mutex_init(&data->mutexes[i], NULL))
			return (printf("philo: Error making mutex\n"), 1);
		data->mutex_count++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (printf("philo: Error making mutex\n"), 1);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (printf("philo: Error making mutex\n"), 1);
	return (0);
}

short	initialize_data(t_data *data, t_philo **philos, char **argv)
{
	if (validation_handler(argv))
		return (printf("philo: %s", USAGE), 2);
	data->philos_num = ft_atoui(argv[1]);
	data->time_to_die = ft_atoui(argv[2]);
	data->time_to_eat = ft_atoui(argv[3]);
	data->time_to_sleep = ft_atoui(argv[4]);
	if (argv[5])
		data->eats_num = ft_atoui(argv[5]);
	else
		data->eats_num = -1;
	if (!data->philos_num || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep || !data->eats_num)
		return (printf("philo: %s", USAGE), 2);
	data->threads = (pthread_t *)malloc(sizeof(pthread_t) * data->philos_num);
	data->mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philos_num);
	*philos = (t_philo *)malloc(sizeof(t_philo) * data->philos_num);
	if (!data->mutexes || !data->threads || !*philos)
		return (printf("philo: Memory allocation error\n"), 1);
	data->stopped = false;
	return (initialize_mutexes(data));
}
