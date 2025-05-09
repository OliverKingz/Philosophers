/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:47:31 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/06 20:38:27 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*admin_routine(void *arg)
{
	t_admin	*data;
	int		i;
	int		philos_full;

	data = (t_admin *)arg;
	while (TRUE)
	{
		usleep(500);
		philos_full = 0;
		i = -1;
		while (++i < (int)data->philo_count)
		{
			if (!is_simulation_running(data))
				return (NULL);
			pthread_mutex_lock(&data->philos[i].meal_lock);
			if (check_philo_death(data, &data->philos[i]))
				return (NULL);
			check_philo_finish(data, &data->philos[i], &philos_full);
			pthread_mutex_unlock(&data->philos[i].meal_lock);
		}
		if (data->min_meals != -1 && philos_full == (int)data->philo_count)
			return (stop_simulation_run(data), NULL);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->admin->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo->admin, philo, MSG_FORK);
		usleep(philo->admin->time_to_die * MSEC_TO_USEC);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (is_simulation_running(philo->admin))
	{
		philo_take_forks(philo);
		philo_eats(philo);
		philo_release_forks(philo);
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (NULL);
}

void	wait_threads_finish(t_admin *data)
{
	int	i;

	if (data->admin_thread)
		pthread_join(data->admin_thread, NULL);
	if (data->philos)
	{
		i = -1;
		while (++i < (int)data->philo_count)
			pthread_join(data->philos[i].thread, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_admin	data;
	int		i;

	if (argc < 5 || argc > 6)
		return (printf("%s%s%s%s", USE1, USE2, USE3, EXAMPLE), EXIT_FAILURE);
	if (init_admin(argc, argv, &data) == FALSE)
		return (printf("%s\n", ERR_INPUT), EXIT_FAILURE);
	i = -1;
	while (++i < (int)data.philo_count)
	{
		pthread_create(&data.philos[i].thread, NULL, philo_routine,
			&data.philos[i]);
	}
	if (pthread_create(&data.admin_thread, NULL, admin_routine, &data) != 0)
		return (wait_threads_finish(&data), clean_and_destroy(&data), 1);
	wait_threads_finish(&data);
	clean_and_destroy(&data);
	return (EXIT_SUCCESS);
}
