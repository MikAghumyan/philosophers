/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:45:26 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/03 00:32:46 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

unsigned int	ft_atoui(const char *nptr)
{
	int i;
	int result;

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