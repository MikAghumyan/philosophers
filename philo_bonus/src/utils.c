/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:45:26 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/12 19:28:59 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_currtime();
	while ((get_currtime() - start) < milliseconds)
		usleep(100);
	return (0);
}

size_t	get_currtime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

unsigned int	ft_atoui(const char *nptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (ft_isdigit(nptr[i]))
	{
		if (result * 10 + nptr[i] - '0' < result)
			return (0);
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result);
}
