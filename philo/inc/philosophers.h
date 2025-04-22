/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:46:11 by ozamora-          #+#    #+#             */
/*   Updated: 2025/04/22 16:56:42 by ozamora-         ###   ########.fr       */
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

# define USAGE \
	"Usage:\t ./philo \
	[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] \
	[number_of_times_each_philosopher_must_eat(OPTIONAL)]"
# define EXAMPLE "Example: ./philo 3 400 200 200"

typedef struct s_admin
{
	unsigned int	num_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_eat;
	pthread_t		*philo_thread;
	pthread_mutex_t	*fork;
}	t_admin;

#endif