/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/04 15:12:58 by maghumya         ###   ########.fr       */
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
