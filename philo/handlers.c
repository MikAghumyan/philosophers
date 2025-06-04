/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:26:22 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/04 21:49:51 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_exit(t_data *data, t_philo **philos)
{
	if (data)
	{
		while (data->mutex_count--)
			pthread_mutex_destroy(&data->mutexes[data->mutex_count]);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->stop_mutex);
		free(data->mutexes);
		data->mutexes = NULL;
		free(data->threads);
		data->threads = NULL;
	}
	if (philos)
	{
		free(*philos);
		*philos = NULL;
	}
}

bool	validation_handler(char **argv)
{
	int i, j;
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (true);
	}
	return (false);
}

bool	print_handler(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%zu %zu %s\n", get_currtime() - philo->data->start_time,
		philo->philo_id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (false);
}
