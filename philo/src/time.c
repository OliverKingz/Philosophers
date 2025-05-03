/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:36:53 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/03 23:37:03 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
