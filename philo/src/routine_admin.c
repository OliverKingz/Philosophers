/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_admin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:01:31 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/05 01:25:15 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	simulation_running(t_admin *data)
{
	pthread_mutex_lock(&data->sim_lock);
	if (!data->running)
	{
		pthread_mutex_unlock(&data->sim_lock);
		return (FALSE) ;
	}
	pthread_mutex_unlock(&data->sim_lock);
	return (TRUE);
}
