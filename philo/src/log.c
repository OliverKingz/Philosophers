/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:07:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/04 22:51:37 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

const char	*assign_color(int id)
{
	static const char *colors[] = {
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
	};
	return (colors[id % 6]);
}

// [timestamp] Philosopher X action
void print_log(t_admin *data, t_philo *philo, const char *msg)
{
	unsigned long time;

	pthread_mutex_lock(&data->print_mutex);
	time = get_elapsed_time_usec(data) / MSEC_TO_USEC;
	printf("%s[%lums] Philosopher %d %s\033[0m\n",
			assign_color(philo->id),
			time,
			philo->id,
			msg);
	pthread_mutex_unlock(&philo->admin->print_mutex);
}
