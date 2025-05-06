/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_admin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:01:31 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/06 20:38:27 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_simulation_running(t_admin *data)
{
	pthread_mutex_lock(&data->run_lock);
	if (!data->is_running)
	{
		pthread_mutex_unlock(&data->run_lock);
		return (FALSE);
	}
	pthread_mutex_unlock(&data->run_lock);
	return (TRUE);
}

void	stop_simulation_run(t_admin *data)
{
	pthread_mutex_lock(&data->run_lock);
	data->is_running = FALSE;
	pthread_mutex_unlock(&data->run_lock);
}

int	check_philo_death(t_admin *data, t_philo *philo)
{
	if (get_current_time_ms() - philo->lastmeal_time > data->time_to_die)
	{
		print_log(data, philo, MSG_DEAD);
		stop_simulation_run(data);
		pthread_mutex_unlock(&philo->meal_lock);
		return (TRUE);
	}
	return (FALSE);
}

int	check_philo_finish(t_admin *data, t_philo *philo, int *philos_full)
{
	if (philo->is_finished == FALSE)
	{
		if (data->min_meals != -1 && philo->meals_eaten >= data->min_meals)
		{
			philo->is_finished = TRUE;
			print_log(data, philo, MSG_FINISH);
			return ((*philos_full)++, TRUE);
		}
		return (FALSE);
	}
	else
		return ((*philos_full)++, TRUE);
}
