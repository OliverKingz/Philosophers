/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:22:08 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/05 16:32:17 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo->admin, philo, MSG_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_log(philo->admin, philo, MSG_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_log(philo->admin, philo, MSG_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_log(philo->admin, philo, MSG_FORK);
	}
}

void	philo_eats(t_philo *philo)
{
	t_admin	*data;

	data = philo->admin;
	pthread_mutex_lock(&philo->meal_lock);
	philo->lastmeal_time = get_current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_log(data, philo, MSG_EAT);
	usleep(data->time_to_eat * MSEC_TO_USEC);
}

void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
