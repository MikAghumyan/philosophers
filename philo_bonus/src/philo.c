/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:49:40 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/11 20:22:30 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (true)
	{
		sem_wait(philo->data->meal_sem);
		if (philo->data->eats_num > 0
			&& philo->eat_counter >= (size_t)philo->data->eats_num)
		{
			philo->ended = true;
			sem_post(philo->data->philos_finished_sem);
			sem_post(philo->data->meal_sem);
			return (0);
		}
		if (get_currtime() - philo->last_eat > philo->data->time_to_die)
		{
			sem_wait(philo->data->print_sem);
			printf("%zu %zu %s\n", get_currtime() - philo->data->start_time,
				philo->philo_id + 1, DIED);
			sem_post(philo->data->stop_sem);
			exit(1);
		}
		sem_post(philo->data->meal_sem);
		usleep(100);
	}
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
	pthread_create(&monitor_thread, NULL, philo_monitor, &philo);
	philo_routine(data, &philo);
	pthread_join(monitor_thread, NULL);
	return (0);
}
