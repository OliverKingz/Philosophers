/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:47:31 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/04 20:40:57 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*admin_routine(void *arg)
{
	t_admin	*data;

	data = (t_admin *)arg;		
	while (1)
	{
		if (!simulation_active(data))
			break ;
		usleep(1 * MSEC_TO_USEC);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_admin	*data;

	philo = (t_philo *)arg;
	data = philo->admin;
	while (1)
	{
		if (!simulation_active(data))
			break ;

		// Philosopher tries to pick up forks
		if (philo->id % 2 == 1)
			(pthread_mutex_lock(philo->l_fork),
				pthread_mutex_lock(philo->r_fork));
		else
			usleep(MIN_WAIT);

		// Philosopher eats
		pthread_mutex_lock(&philo->meal_mutex);
		philo->lastmeal_time = get_current_time(data);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);

		usleep(data->time_to_eat * MSEC_TO_USEC);

		// Philosophers puts down forks
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);

		// Philosopher sleeps
		usleep(data->time_to_sleep * MSEC_TO_USEC);

		// Philosopher thinks (delay)
		usleep(MIN_WAIT);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_admin	data;
	int		i;

	if (argc <= 5 || argc > 6)
		return (printf("%s\n%s\n", USAGE, EXAMPLE), EXIT_FAILURE);
	if (init_admin(argc, argv, &data) == FALSE)
		return (printf("%s\n", ERR_INPUT), EXIT_FAILURE);
	i = 0;
	while (i < data.num_philo)
	{
		pthread_create(&data.philos[i].philo_thread, NULL, philo_routine,
			&data.philos[i]);
		i++;
	}
	if (pthread_create(&data.admin_thread, NULL, admin_routine, &data) != 0)
		return (free(data.philos), free(data.forks), FALSE);
	pthread_join(data.admin_thread, NULL);
	clean_and_destroy(&data);
	return (0);
}
