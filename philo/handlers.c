/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:26:22 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/03 14:52:05 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_exit(t_data *data)
{
	if (data)
	{
		while (data->mutex_count--)
			pthread_mutex_destroy(&data->mutexes[data->mutex_count]);
		free(data->mutexes);
		data->mutexes = NULL;
		free(data->threads);
		data->threads = NULL;
	}
}
