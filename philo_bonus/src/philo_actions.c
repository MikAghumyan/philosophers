/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:02:36 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/10 21:50:35 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	handle_forks(t_data *data, t_philo *philo)
{
	sem_wait(data->forks_sem);
	if (print_handler(data, philo, FORK))
	{
		sem_post(data->forks_sem);
		return (true);
	}
	sem_wait(data->forks_sem);
	if (print_handler(data, philo, FORK))
	{
		sem_post(data->forks_sem);
		sem_post(data->forks_sem);
		return (true);
	}
	return (false);
}

bool	handle_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eat = get_currtime();
	if (data->eats_num > 0)
		philo->eat_counter++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (print_handler(data, philo, EAT))
	{
		sem_post(data->forks_sem);
		sem_post(data->forks_sem);
		return (true);
	}
	ft_usleep(data->time_to_eat);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	return (false);
}

bool	handle_think(t_data *data, t_philo *philo)
{
	if (print_handler(data, philo, THINK))
		return (true);
	return (false);
}

bool	handle_sleep(t_data *data, t_philo *philo)
{
	if (print_handler(data, philo, SLEEP))
		return (true);
	ft_usleep(data->time_to_sleep);
	return (false);
}