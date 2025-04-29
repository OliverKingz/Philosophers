/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:45:55 by ozamora-          #+#    #+#             */
/*   Updated: 2025/04/28 16:29:42 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	my_is_unsigned_nbr(const char *str)
{
	if (str == NULL)
		return (FALSE);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '+')
			str++;
		if (*str == '-')
			return (FALSE);
	}
	if (*str == '\0')
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	while (ft_isspace(*str))
		str++;
	if (*str != '\0')
		return (FALSE);
	return (TRUE);
}

unsigned int	my_atoui(const char *str)
{
	unsigned int	result;
	int				i;

	result = 0;
	i = 0;
	while (ft_isspace(*str))
		str++;
	if (str[i] == '+')
		i++;
	if (*str == '\0')
		return (FALSE);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (UINT_MAX - (str[i] - '0')) / 10)
			return 0; // Overflow, return 0 or handle as needed
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return result;
}
