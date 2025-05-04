/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:47:31 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/04 22:58:18 by ozamora-         ###   ########.fr       */
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
		usleep(10 * MSEC_TO_USEC);
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
		philo_takes_forks(philo);
		philo_eats(philo);
		philo_leaves_forks(philo);
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
	return (EXIT_SUCCESS);
}
