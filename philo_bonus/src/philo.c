/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:49:40 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/10 21:47:34 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_monitor(void *args)
{
	(void)args;
	return (0);
}

short	philo_routine(t_data *data, t_philo *philo)
{
	while (true)
	{
		if (handle_think(data, philo))
			break ;
		if (handle_forks(data, philo))
			break ;
		if (handle_eat(data, philo))
			break ;
		if (handle_sleep(data, philo))
			break ;
	}
	return (0);
}

short	start_philo(t_data *data, size_t id)
{
	t_philo		philo;
	pthread_t	monitor_thread;

	philo.philo_id = id;
	philo.eat_counter = 0;
	philo.ended = false;
	philo.last_eat = get_currtime();
	philo.data = data;
	if (pthread_mutex_init(&(philo.meal_mutex), NULL))
		return (-1);
	if (pthread_mutex_init(&(philo.stop_mutex), NULL))
		return (-1);
	pthread_create(&monitor_thread, NULL, philo_monitor, &philo);
	philo_routine(data, &philo);
	pthread_join(monitor_thread, NULL);
	pthread_mutex_destroy(&(philo.meal_mutex));
	pthread_mutex_destroy(&(philo.stop_mutex));
	return (0);
}
