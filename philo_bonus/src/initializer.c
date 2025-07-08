/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 00:36:54 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/08 15:39:24 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

short	initialize_data(t_data *data, char **argv)
{
	if (validation_handler(argv))
		return (printf("philo: %s", USAGE), 2);
	data->philos_num = ft_atoui(argv[1]);
	data->time_to_die = ft_atoui(argv[2]);
	data->time_to_eat = ft_atoui(argv[3]);
	data->time_to_sleep = ft_atoui(argv[4]);
	if (argv[5])
		data->eats_num = ft_atoui(argv[5]);
	else
		data->eats_num = -1;
	if (!data->philos_num || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep || !data->eats_num)
		return (printf("philo: %s", USAGE), 2);
	sem_unlink("/forks");
	sem_unlink("/write_lock");
	sem_unlink("/stop_sim");
	data->forks_sem = sem_open("/forks", O_CREAT, 0644, data->philos_num);
	data->write_sem = sem_open("/write_lock", O_CREAT, 0644, 1);
	data->write_sem = sem_open("/stop_sim", O_CREAT, 0644, 0);
	return (0);
}
