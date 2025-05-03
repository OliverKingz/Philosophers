/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:47:31 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/03 23:34:43 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_admin(int argc, char **argv, t_admin *data)
{
	struct timeval	start_time;
	unsigned int	i;

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
		return (free(data->forks), (FALSE));
	return (TRUE);
}

int	init_philos(t_admin *data)
{
	data->philos = malloc(data->num_philo * sizeof(t_philo));
	if (!data->philos)
		return (FALSE);
	for (unsigned int i = 0; i < data->num_philo; i++)
	{
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->num_philo];
		data->philos[i].lastmeal_time = data->start_time;
		data->philos[i].meals_eaten = 0;
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
	}
	return (TRUE);
}

unsigned long	get_current_time(t_admin *data)
{
	struct timeval	current_time;
	unsigned long	elapsed_time;

	if (gettimeofday(&current_time, NULL) != 0)
		return (0);
	elapsed_time = ((current_time.tv_sec * SEC_TO_USEC + current_time.tv_usec)
			- data->start_time) / MSEC_TO_USEC;
	return (elapsed_time);
}

void	*admin_routine(void *arg)
{
	t_admin	*data;

	data = (t_admin *)arg;
}

void	*philo_routine(void *arg)
{
	t_admin	*data;

	data = (t_admin *)arg;
}

int	main(int argc, char **argv)
{
	t_admin	data;
	int		i;

	if (argc <= 5 || argc > 6)
		printf("%s\n%s\n", USAGE, EXAMPLE);
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
