/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:18:12 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/03 14:19:17 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;
	if (argc < 5 || argc > 6)
		handle_error(USAGE, NULL);
	initialize_data(&data, argv);
	handle_exit(&data);
	return (0);
}