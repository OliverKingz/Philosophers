/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:46:11 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/06 20:37:20 by ozamora-         ###   ########.fr       */
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

# define USE1 "Usage:\t ./philo "
# define USE2 "<number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> "
# define USE3 "[<number_of_times_each_philosopher_must_eat>]\n"
# define EXAMPLE "Example: ./philo 3 400 200 200\n"

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DEAD "died"
# define MSG_FINISH "finished eating"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"

# define ERR_INPUT "Error: Invalid input"

# define MAX_PHILO 200
# define MIN_WAIT 1000

# define SEC_TO_USEC 1000000
# define SEC_TO_MSEC 1000
# define MSEC_TO_USEC 1000

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	struct s_admin	*admin;
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	unsigned long	lastmeal_time;
	int				meals_eaten;
	int				is_finished;
}					t_philo;

typedef struct s_admin
{
	unsigned int	philo_count;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				min_meals;
	unsigned long	start_time;
	pthread_t		admin_thread;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	run_lock;
	int				is_running;
}					t_admin;

// main.c

void				*admin_routine(void *arg);
void				*philo_routine(void *arg);
void				wait_threads_finish(t_admin *data);

// init.c

int					init_admin(int argc, char **argv, t_admin *data);
int					setup_philos(t_admin *data);
int					arg_to_admin(int argc, char **argv, t_admin *data);
void				clean_and_destroy(t_admin *data);

// time.c

unsigned long		get_elapsed_time_ms(t_admin *data);
unsigned long		get_current_time_ms(void);

// routine_admin.c

int					is_sim_running(t_admin *data);
void				stop_simulation_run(t_admin *data);
int					check_philo_death(t_admin *data, t_philo *philo);
int					check_philo_finish(t_admin *data, t_philo *philo,
						int *philos_full);

// routine_philo.c

void				philo_take_forks(t_philo *philo);
void				philo_eats(t_philo *philo);
void				philo_release_forks(t_philo *philo);
void				philo_sleeps(t_philo *philo);
void				philo_thinks(t_philo *philo);

// log.c

const char			*assign_color(int id);
void				print_log(t_admin *data, t_philo *philo, const char *msg);

// utils.c

int					is_positive_nbr(const char *str);
unsigned int		my_atoui(const char *str);
int					ft_isspace(int c);
int					ft_isdigit(int c);

#endif