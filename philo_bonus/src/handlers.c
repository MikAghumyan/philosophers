/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:26:22 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/11 20:56:46 by maghumya         ###   ########.fr       */
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
	sem_unlink("/meal_lock");
	exit(exit_status);
}

void	handle_finish(t_data *data)
{
	size_t	i;

	sem_wait(data->stop_sem);
	i = -1;
	while (++i < data->philos_num)
		sem_post(data->philos_finished_sem);
	i = -1;
	while (++i < data->philos_num)
		kill(data->pid_arr[i], SIGKILL);
	i = -1;
	while (++i < data->philos_num)
		waitpid(data->pid_arr[i], NULL, 0);
	if (data->time_to_eat > 0)
		pthread_join(data->monitor_thread, NULL);
	handle_exit(data, 0);
}

bool	print_handler(t_data *data, t_philo *philo, char *msg)
{
	bool	should_stop;

	should_stop = philo->ended;
	if (!should_stop)
	{
		sem_wait(data->print_sem);
		printf("%zu %zu %s\n", get_currtime() - philo->data->start_time,
			philo->philo_id + 1, msg);
		sem_post(data->print_sem);
	}
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
