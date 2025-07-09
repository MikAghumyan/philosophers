/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:49:40 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/09 20:07:23 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_monitor(void *args)
{
	(void)args;
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
	pthread_create(&monitor_thread, NULL, philo_monitor, &philo);
	pthread_join(monitor_thread, NULL);
	while (true)
	{
	}
	pthread_mutex_destroy(&(philo.meal_mutex));
	return (0);
}
