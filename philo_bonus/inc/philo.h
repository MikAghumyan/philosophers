/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:57:47 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/08 15:37:11 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"
# define USAGE \
	"Usage: ./philo [number of philosophers] [time to die] [time to eat]\
 [time to sleep] [number of times to eat each (optional)]\n"

typedef struct s_data
{
	size_t		philos_num;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	ssize_t		eats_num;
	ssize_t		start_time;

	sem_t		*forks_sem;
	sem_t		*write_sem;
	sem_t		*stop_sem;
}				t_data;

int				ft_usleep(size_t milliseconds);
size_t			get_currtime(void);
int				ft_isdigit(int c);
unsigned int	ft_atoui(const char *nptr);

short			initialize_data(t_data *data, char **argv);

bool			validation_handler(char **argv);

#endif