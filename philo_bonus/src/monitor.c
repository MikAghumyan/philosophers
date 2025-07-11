/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:38:55 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/11 20:34:09 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor_finished(void *args)
{
	t_data	*data;
	size_t	i;

	data = (t_data *)args;
	i = -1;
	while (++i < data->philos_num)
	{
		sem_wait(data->philos_finished_sem);
	}
	sem_post(data->stop_sem);
	i = -1;
	return (0);
}
