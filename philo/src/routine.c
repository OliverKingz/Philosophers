/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:22:08 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/04 20:42:36 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	simulation_active(t_admin *data)
{
	pthread_mutex_lock(&data->sim_mutex);
	if (!data->sim_active)
	{
		pthread_mutex_unlock(&data->sim_mutex);
		return (FALSE) ;
	}
	pthread_mutex_unlock(&data->sim_mutex);
	return (TRUE);
}
