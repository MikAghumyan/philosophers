/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:18:12 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/04 18:29:15 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;
	t_philo *philos;
	short exit_status;

	if (argc < 5 || argc > 6)
		return (printf("philo: %s", USAGE), 1);
	exit_status = initialize_data(&data, &philos, argv);
	if (exit_status == 1)
		return (handle_exit(&data, &philos), exit_status);
	else if (exit_status == 2)
		return (handle_exit(NULL, NULL), exit_status);
	exit_status = initialize_threads(&data, &philos);
	join_threads(&data);
	handle_exit(&data, &philos);
	return (exit_status);
}