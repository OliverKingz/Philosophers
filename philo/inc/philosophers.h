/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:46:11 by ozamora-          #+#    #+#             */
/*   Updated: 2025/03/03 01:19:32 by ozamora-         ###   ########.fr       */
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

// - memset: to set memory with a constant byte
// - printf: to print formatted output
// - malloc: to allocate memory dynamically
// - free: to deallocate memory
// - write: to write data to a file descriptor
// - usleep: to suspend execution for microsecond intervals
// - gettimeofday: to get the current time
// - pthread_create: to create a new thread
// - pthread_detach: to detach a thread
// - pthread_join: to join with a terminated thread
// - pthread_mutex_init: to initialize a mutex
// - pthread_mutex_destroy: to destroy a mutex
// - pthread_mutex_lock: to lock a mutex
// - pthread_mutex_unlock: to unlock a mutex

// void		*memset(void *s, int c, size_t n);
// int		printf(const char *format, ...);
// void		*malloc(size_t size);
// void		free(void *ptr);
// ssize_t	write(int fd, const void *buf, size_t count);
// int		usleep(useconds_t usec);
// int		gettimeofday(struct timeval *tv, struct timezone *tz);
// int		pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
// int		pthread_detach(pthread_t thread);
// int		pthread_join(pthread_t thread, void **retval);
// int		pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
// int		pthread_mutex_destroy(pthread_mutex_t *mutex);
// int		pthread_mutex_lock(pthread_mutex_t *mutex);
// int		pthread_mutex_unlock(pthread_mutex_t *mutex);


# endif