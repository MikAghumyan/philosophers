/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:57:47 by maghumya          #+#    #+#             */
/*   Updated: 2025/07/12 14:38:26 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
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
	sem_t		*philos_finished_sem;
	sem_t		*print_sem;
	sem_t		*meal_sem;
	pid_t		*pid_arr;
	pthread_t	monitor_thread;
}				t_data;

typedef struct s_philo
{
	size_t		philo_id;
	size_t		eat_counter;
	size_t		last_eat;
	bool		ended;
	t_data		*data;
}				t_philo;

int				ft_usleep(size_t milliseconds);
size_t			get_currtime(void);
int				ft_isdigit(int c);
unsigned int	ft_atoui(const char *nptr);

short			initialize_semaphores(t_data *data);
short			initialize_data(t_data *data, char **argv);
short			initialize_processes(t_data *data);

bool			validation_handler(char **argv);
bool			print_handler(t_data *data, t_philo *philo, char *msg);
void			handle_exit(t_data *data, short exit_status);
void			handle_finish(t_data *data);
void			*main_monitor_handler(void *args);

void			*philo_monitor(void *args);
short			start_philo(t_data *data, size_t id);
short			philo_routine(t_data *data, t_philo *philo);

bool			handle_forks(t_data *data, t_philo *philo);
bool			handle_eat(t_data *data, t_philo *philo);
bool			handle_think(t_data *data, t_philo *philo);
bool			handle_sleep(t_data *data, t_philo *philo);
#endif