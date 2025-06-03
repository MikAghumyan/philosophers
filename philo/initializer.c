/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:42:49 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/03 15:03:55 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_valid_args(char **argv)
{
	int i, j;
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return (true);
			}
		}
	}
	return (false);
}

short	initialize_mutexes(t_data *data)
{
	size_t	i;

	i = -1;
	data->mutex_count = 0;
	while (++i < data->philos_num)
	{
		if (pthread_mutex_init(&data->mutexes[i], NULL))
			return (printf("fdf: Error making mutex\n"), 1);
		data->mutex_count++;
	}
	return (0);
}

short	initialize_data(t_data *data, char **argv)
{
	if (check_valid_args(argv))
		return (printf("fdf: %s", USAGE), 2);
	data->philos_num = ft_atoui(argv[1]);
	data->time_to_die = ft_atoui(argv[2]);
	data->time_to_eat = ft_atoui(argv[3]);
	data->time_to_sleep = ft_atoui(argv[4]);
	if (!data->philos_num || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep)
		return (printf("fdf: %s", USAGE), 2);
	if (argv[5])
		data->eats_num = ft_atoui(argv[5]);
	else
		data->eats_num = -1;
	data->threads = (pthread_t *)malloc(sizeof(pthread_t) * data->philos_num);
	data->mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philos_num);
	if (!data->mutexes || !data->threads)
		return (printf("fdf: Memory allocation error\n"), 1);
	return (initialize_mutexes(data));
}
