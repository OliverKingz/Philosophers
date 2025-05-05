/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:35:52 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/05 18:30:32 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_admin(int argc, char **argv, t_admin *data)
{
	int	i;

	memset(data, '\0', sizeof(t_admin));
	if (!arg_to_admin(argc, argv, data))
		return (FALSE);
	data->running = TRUE;
	data->start_time = get_current_time_ms();
	data->forks = malloc(data->philo_count * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (FALSE);
	i = -1;
	while (++i < (int)data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->sim_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	if (!setup_philos(data))
		return (clean_and_destroy(data), (FALSE));
	return (TRUE);
}

int	arg_to_admin(int argc, char **argv, t_admin *data)
{
	if (!my_is_unsigned_nbr(argv[1]) || !my_is_unsigned_nbr(argv[2])
		|| !my_is_unsigned_nbr(argv[3]) || !my_is_unsigned_nbr(argv[4])
		|| (argc == 6 && !my_is_unsigned_nbr(argv[5])))
		return (FALSE);
	data->philo_count = my_atoui(argv[1]);
	data->time_to_die = my_atoui(argv[2]);
	data->time_to_eat = my_atoui(argv[3]);
	data->time_to_sleep = my_atoui(argv[4]);
	data->min_meals = -1;
	if (argc == 6)
		data->min_meals = (int)my_atoui(argv[5]);
	if (data->philo_count > MAX_PHILO)
		return (FALSE);
	return (TRUE);
}

int	setup_philos(t_admin *data)
{
	int i;

	data->philos = malloc(data->philo_count * sizeof(t_philo));
	if (!data->philos)
		return (FALSE);
	i = 0;
	while (i < (int)data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		data->philos[i].lastmeal_time = data->start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].is_finished = FALSE;
		data->philos[i].admin = data;
		pthread_mutex_init(&data->philos[i].meal_lock, NULL);
		i++;
	}
	return (TRUE);
}

void	clean_and_destroy(t_admin *data)
{
	int i;

	if (!data)
		return ;
	if (data->forks)
	{
		i = -1;
		while (++i < (int)data->philo_count)
			pthread_mutex_destroy(&data->forks[i]);
		(free(data->forks), data->forks = NULL);
	}
	if (data->philos)
	{
		i = -1;
		while (++i < (int)data->philo_count)
		{
			pthread_mutex_destroy(&data->philos[i].meal_lock);
			data->philos[i].left_fork = NULL;
			data->philos[i].right_fork = NULL;
		}
		(free(data->philos), data->philos = NULL);
	}
	pthread_mutex_destroy(&data->sim_lock);
	pthread_mutex_destroy(&data->print_lock);
}
