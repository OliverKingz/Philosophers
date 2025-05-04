/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:22:08 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/04 23:02:43 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_takes_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	print_log(philo->admin, philo, MSG_FORK);
}

void	philo_eats(t_philo *philo)
{
	t_admin	*data;

	data = philo->admin;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->lastmeal_time = get_elapsed_time_usec(data);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_log(data, philo, MSG_EAT);
	usleep(data->time_to_eat * MSEC_TO_USEC);
}

void	philo_leaves_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleeps(t_philo *philo)
{
	print_log(philo->admin, philo, MSG_SLEEP);
	usleep(philo->admin->time_to_sleep * MSEC_TO_USEC);
}

void	philo_thinks(t_philo *philo)
{
	print_log(philo->admin, philo, MSG_THINK);
	usleep(MIN_WAIT);
}
