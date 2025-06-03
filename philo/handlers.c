/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:26:22 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/03 14:05:10 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_error(char *err_msg, t_data *data)
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
	printf("philo: %s", err_msg);
	exit(1);
}
