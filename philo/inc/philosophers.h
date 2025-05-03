/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:46:11 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/03 23:22:30 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>  // To use pthread_create, pthread_detach, pthread_join
# include <stdio.h>    // To use printf
# include <stdlib.h>   // To use malloc, free
# include <string.h>   // To use memset
# include <sys/time.h> // To use gettimeofday
# include <unistd.h>   // To use write, usleep
						// pthread_mutex_init, pthread_mutex_destroy
						// pthread_mutex_lock, pthread_mutex_unlock
# include <limits.h>

# ifndef MAX_PHILO
#  define MAX_PHILO 200
# endif

# define USAGE \
	"Usage:\t ./philo \
	<number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> \
	[<number_of_times_each_philosopher_must_eat>]"
# define EXAMPLE "Example: ./philo 3 400 200 200"

# define ERR_INPUT "Error: input"

# define SEC_TO_USEC 1000000
# define MSEC_TO_USEC 1000

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int				id;
	pthread_t		philo_thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	unsigned long	lastmeal_time;
	pthread_mutex_t	meal_mutex;
	int				meals_eaten;
}					t_philo;

typedef struct s_admin
{
	unsigned int	num_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_eat;
	pthread_t		admin_thread;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	print_mutex;
	int				sim_active;
	unsigned long	start_time;
}					t_admin;

int					init_admin(int argc, char **argv, t_admin *data);
int					init_philos(t_admin *data);
unsigned long		get_current_time(t_admin *data);
void				*admin_routine(void *arg);
void				*philo_routine(void *arg);
void				clean_and_destroy(t_admin *data);

long				ft_atol(const char *nptr);
int					check_args_int(char **args);

#endif