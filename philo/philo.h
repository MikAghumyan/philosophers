/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:42:31 by maghumya          #+#    #+#             */
/*   Updated: 2025/06/04 19:01:10 by maghumya         ###   ########.fr       */
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
	size_t			philos_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	ssize_t			eats_num;
	ssize_t			start_time;

	bool			stopped;

	pthread_mutex_t	*mutexes;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	size_t			mutex_count;
	pthread_t		*threads;
}					t_data;

typedef struct s_philo
{
	size_t			philo_id;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	size_t			eat_counter;
	t_data			*data;
}					t_philo;

void				handle_exit(t_data *data, t_philo **philos);
bool				validation_handler(char **argv);
bool				print_handler(t_philo *philo, char *msg);

short				initialize_data(t_data *data, t_philo **philos,
						char **argv);
short				initialize_mutexes(t_data *data);
short				initialize_threads(t_data *data, t_philo **philos);
short				initialize_forks(t_data *data, t_philo *philo);

short				handle_eat(t_philo *philo, t_data *data);
short				handle_think(t_philo *philo, t_data *data);
short				handle_sleep(t_philo *philo, t_data *data);
short				handle_forks(t_philo *philo, t_data *data);

short				join_threads(t_data *data);
void				*start_philo(void *args);

int					ft_isdigit(int c);
unsigned int		ft_atoui(const char *nptr);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);

#endif