/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:36:53 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/05 18:47:04 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_current_time_ms(void)
{
	struct timeval	tv;
	unsigned long	current_time;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	current_time = ((tv.tv_sec * SEC_TO_MSEC + (tv.tv_usec / MSEC_TO_USEC)));
	return (current_time);
}

unsigned long	get_elapsed_time_ms(t_admin *data)
{
	unsigned long	elapsed_time;

	elapsed_time = get_current_time_ms() - data->start_time;
	return (elapsed_time);
}
