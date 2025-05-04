/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:47:31 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/05 01:28:24 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*admin_routine(void *arg)
{
	t_admin	*data;
	int		i;

	data = (t_admin *)arg;
	while (TRUE)
	{
		usleep(1 * MSEC_TO_USEC);
		if (!simulation_running(data))
			break ;
		i = 0;
		while (i < (int)data->philo_count)
		{
			pthread_mutex_lock(&data->philos[i].meal_lock);
			if (get_current_time_ms() - data->philos[i].lastmeal_time > data->time_to_die)
			{
				pthread_mutex_lock(&data->sim_lock);
				data->running = 0;
				pthread_mutex_unlock(&data->sim_lock);
				print_log(data, &data->philos[i], MSG_DEAD);
				pthread_mutex_unlock(&data->philos[i].meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			i++;
		}
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_admin	*data;

	philo = (t_philo *)arg;
	data = philo->admin;
	while (TRUE)
	{
		if (!simulation_running(data))
			break ;
		philo_take_forks(philo);
		philo_eats(philo);
		philo_release_forks(philo);
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_admin			data;
	unsigned int	i;

	if (argc < 5 || argc > 6)
		return (printf("%s\n%s\n", USAGE, EXAMPLE), EXIT_FAILURE);
	if (init_admin(argc, argv, &data) == FALSE)
		return (printf("%s\n", ERR_INPUT), EXIT_FAILURE);
	i = 0;
	while (i < data.philo_count)
	{
		pthread_create(&data.philos[i].thread, NULL, philo_routine,
			&data.philos[i]);
		i++;
	}
	if (pthread_create(&data.admin_thread, NULL, admin_routine, &data) != 0)
		return (free(data.philos), free(data.forks), FALSE);
	pthread_join(data.admin_thread, NULL);
	clean_and_destroy(&data);
	return (EXIT_SUCCESS);
}
