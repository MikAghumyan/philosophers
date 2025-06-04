/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:33:57 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/04 18:28:18 by maghumya         ###   ########.fr       */
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
