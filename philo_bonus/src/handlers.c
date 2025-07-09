/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:26:22 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/09 18:17:01 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	handle_exit(t_data *data, short exit_status)
{
	free(data->pid_arr);
	exit(exit_status);
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
