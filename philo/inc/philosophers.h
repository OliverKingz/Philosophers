/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:46:11 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/03 22:49:12 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>	// To use memset
# include <stdio.h>		// To use printf
# include <stdlib.h>	// To use malloc, free
# include <unistd.h>	// To use write, usleep
# include <sys/time.h>	// To use gettimeofday
# include <pthread.h>	// To use pthread_create, pthread_detach, pthread_join
						// pthread_mutex_init, pthread_mutex_destroy
						// pthread_mutex_lock, pthread_mutex_unlock
# include <limits.h>

#ifndef MAX_PHILO
# define MAX_PHILO 200
#endif

# define USAGE "Usage:\t ./philo \
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
	unsigned int	num_eat;
	pthread_t		thread_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	unsigned long	t_last_meal;
}					t_philo;

typedef struct s_admin
{
	struct timeval	t_start;
	struct timeval	t_end;
	unsigned long	t_elapsed;
	unsigned int	num_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_eat;
	pthread_t		*admin_thread;
	struct t_philo	*philo_thread;
	pthread_mutex_t	*forks;
	int				sim_active;
}					t_admin;

long	ft_atol(const char *nptr);
int		check_args_int(char **args);

#endif