/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 00:09:43 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/12 15:14:33 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	short	exit_status;

	if (argc < 5 || argc > 6)
		return (printf("philo: %s", USAGE), 1);
	exit_status = initialize_data(&data, argv);
	if (exit_status)
		exit(exit_status);
	exit_status = initialize_processes(&data);
	if (exit_status)
		handle_exit(&data, exit_status);
	if (data.eats_num > 0)
		pthread_create(&data.monitor_thread, NULL, main_monitor_handler, &data);
	handle_finish(&data);
	return (0);
}
