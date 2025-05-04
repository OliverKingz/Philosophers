/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:36:53 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/05 00:39:57 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_elapsed_time_usec(t_admin *data)
{
	unsigned long	elapsed_time;

	elapsed_time = get_current_time_usec() - data->start_time;
	return (elapsed_time);
}

unsigned long	get_current_time_usec(void)
{
	struct timeval	time;
	unsigned long	current_time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	current_time = ((time.tv_sec * SEC_TO_USEC + time.tv_usec));
	return (current_time);
}
