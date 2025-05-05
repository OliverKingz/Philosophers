/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:07:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/05 20:00:55 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

const char	*assign_color(int id)
{
	static const char	*colors[] = {
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
	};

	return (colors[id % 6]);
}

void	print_log(t_admin *data, t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%s%lu %d %s\033[0m\n", assign_color(philo->id),
		get_elapsed_time_ms(data), philo->id, msg);
	pthread_mutex_unlock(&philo->admin->print_lock);
}
