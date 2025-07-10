/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:26:22 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/10 20:48:30 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	handle_exit(t_data *data, short exit_status)
{
	free(data->pid_arr);
	sem_unlink("/forks");
	sem_unlink("/write_lock");
	sem_unlink("/stop_sim");
	sem_unlink("/philos_finished");
	sem_unlink("/print_lock");
	exit(exit_status);
}

bool	print_handler(t_data *data, t_philo *philo, char *msg)
{
	bool	should_stop;

	pthread_mutex_lock(&philo->stop_mutex);
	should_stop = philo->ended;
	if (!should_stop)
	{
		sem_wait(data->print_sem);
		pthread_mutex_unlock(&philo->stop_mutex);
		printf("%zu %zu %s\n", get_currtime() - philo->data->start_time,
			philo->philo_id + 1, msg);
		sem_post(data->print_sem);
	}
	else
		pthread_mutex_unlock(&philo->stop_mutex);
	return (should_stop);
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
