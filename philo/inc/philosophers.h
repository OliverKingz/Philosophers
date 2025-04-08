/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:46:11 by ozamora-          #+#    #+#             */
/*   Updated: 2025/04/08 18:04:28 by ozamora-         ###   ########.fr       */
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


# endif