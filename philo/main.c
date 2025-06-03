/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:18:12 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/03 15:06:47 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;
	short exit_status;

	if (argc < 5 || argc > 6)
		return (printf("fdf: %s", USAGE), 1);
	exit_status = initialize_data(&data, argv);
	if (exit_status == 1)
		return (handle_exit(&data), exit_status);
	else if (exit_status == 2)
		return (handle_exit(NULL), exit_status);
	handle_exit(&data);
	return (0);
}