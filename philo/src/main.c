/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:47:31 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/03 22:48:50 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_admin(int argc, char **argv, t_admin *data)
{
	gettimeofday(&data->t_start, NULL);
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
	data->philo_thread = malloc(data->num_philo * sizeof(pthread_t *));
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t *));
	data->sim_active = TRUE;
	pthread_create(data->admin_thread, NULL, admin_routine, data);
	return (TRUE);
}

unsigned long	calc_elapsed_time(t_admin *data)
{
	gettimeofday(&data->t_end, NULL);
	data->t_elapsed = (data->t_end.tv_sec - data->t_start.tv_sec) * SEC_TO_USEC
		+ (data->t_end.tv_usec - data->t_start.tv_usec);
	return (data->t_elapsed);
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

	if (argc <= 5 || argc > 6)
		printf("%s\n%s\n", USAGE, EXAMPLE);
	if (init_admin(argc, argv, &data) == FALSE)
		return (printf("%s\n", ERR_INPUT), EXIT_FAILURE);
	pthread_join(data.admin_thread, NULL);
	clean_and_destroy();
	return (0);
}
