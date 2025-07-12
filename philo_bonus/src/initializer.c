/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 00:36:54 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/12 15:36:14 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

short	initialize_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/write_lock");
	sem_unlink("/stop_sim");
	sem_unlink("/philos_finished");
	sem_unlink("/print_lock");
	sem_unlink("/meal_lock");
	data->forks_sem = sem_open("/forks", O_CREAT, 0644, data->philos_num);
	if (data->forks_sem == SEM_FAILED)
		return (1);
	data->write_sem = sem_open("/write_lock", O_CREAT, 0644, 1);
	if (data->write_sem == SEM_FAILED)
		return (1);
	data->stop_sem = sem_open("/stop_sim", O_CREAT, 0644, 0);
	if (data->stop_sem == SEM_FAILED)
		return (1);
	data->philos_finished_sem = sem_open("/philos_finished", O_CREAT, 0644, 0);
	if (data->philos_finished_sem == SEM_FAILED)
		return (1);
	data->print_sem = sem_open("/print_lock", O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (1);
	data->meal_sem = sem_open("/meal_lock", O_CREAT, 0644, 1);
	if (data->meal_sem == SEM_FAILED)
		return (1);
	return (0);
}

short	initialize_processes(t_data *data)
{
	size_t	i;
	pid_t	pid_tmp;

	data->start_time = get_currtime();
	i = -1;
	while (++i < data->philos_num)
	{
		pid_tmp = fork();
		if (pid_tmp == -1)
			return (1);
		if (pid_tmp)
			data->pid_arr[i] = pid_tmp;
		else
		{
			start_philo(data, i);
			sem_close(data->meal_sem);
			sem_close(data->forks_sem);
			sem_close(data->write_sem);
			sem_close(data->stop_sem);
			sem_close(data->philos_finished_sem);
			sem_close(data->print_sem);
			exit(0);
		}
	}
	return (0);
}

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
	if (data->philos_num > 200)
		return (printf("philo: too many philosophers\n"), 2);
	if (initialize_semaphores(data))
		return (printf("philo: semaphore initialization failed\n"), 2);
	data->pid_arr = (pid_t *)malloc(sizeof(pid_t) * data->philos_num);
	if (!data->pid_arr)
		return (2);
	return (0);
}
