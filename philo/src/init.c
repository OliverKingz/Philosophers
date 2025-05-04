/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:35:52 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/04 20:24:26 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_admin(int argc, char **argv, t_admin *data)
{
	struct timeval	start_time;
	int	i;

	memset(data, '\0', sizeof(t_admin));
	if (!my_is_unsigned_nbr(argv[1]) || !my_is_unsigned_nbr(argv[2])
		|| !my_is_unsigned_nbr(argv[3]) || !my_is_unsigned_nbr(argv[4])
		|| (argc == 6 && !my_is_unsigned_nbr(argv[5])))
		return (FALSE);
	data->num_philo = my_atoui(argv[1]);
	data->time_to_die = my_atoui(argv[2]);
	data->time_to_eat = my_atoui(argv[3]);
	data->time_to_sleep = my_atoui(argv[4]);
	data->num_eat = UINT_MAX;
	if (argc == 6)
		data->num_eat = my_atoui(argv[5]);
	data->sim_active = TRUE;
	if (gettimeofday(&start_time, NULL) != 0)
		return (FALSE);
	data->start_time = start_time.tv_sec * SEC_TO_USEC + start_time.tv_usec;
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (FALSE);
	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->sim_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	if (!init_philos(data))
		return (clean_and_destroy(data), (FALSE));
	return (TRUE);
}

int	init_philos(t_admin *data)
{
	int i;

	data->philos = malloc(data->num_philo * sizeof(t_philo));
	if (!data->philos)
		return (FALSE);
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->num_philo];
		data->philos[i].lastmeal_time = data->start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].admin = data;
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
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
		while (++i < data->num_philo)
			pthread_mutex_destroy(&data->forks[i]);
		(free(data->forks), data->forks = NULL);
	}
	if (data->philos)
	{
		i = -1;
		while (++i < data->num_philo)
		{
			pthread_mutex_destroy(&data->philos[i].meal_mutex);
			data->philos[i].l_fork = NULL;
			data->philos[i].r_fork = NULL;
		}
		(free(data->philos), data->philos = NULL);
	}
	pthread_mutex_destroy(&data->sim_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}
