/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:42:31 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/03 15:05:46 by maghumya         ###   ########.fr       */
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
	unsigned int	philos_num;
	__useconds_t	time_to_die;
	__useconds_t	time_to_eat;
	__useconds_t	time_to_sleep;
	ssize_t			eats_num;
	pthread_mutex_t	*mutexes;
	size_t			mutex_count;
	pthread_t		*threads;
}					t_data;

typedef struct s_philo
{
	unsigned int	philo_id;
	t_data			*data;
}					t_philo;

void				handle_exit(t_data *data);

bool				check_valid_args(char **argv);
short				initialize_mutexes(t_data *data);
short				initialize_data(t_data *data, char **argv);

unsigned int		ft_atoui(const char *nptr);

#endif