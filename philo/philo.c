/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/03 16:53:01 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	initialize_threads(t_data *data, t_philo **philos)
{
	unsigned int	i;

	i = -1;
	while (++i < data->philos_num)
	{
		(*philos)[i].data = data;
		(*philos)[i].philo_id = i;
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
	t_philo *philo;
	philo = (t_philo *)args;
	printf("thread: %d\t philos_num: %ld\n", philo->philo_id,
		philo->data->mutex_count);
	return (0);
}