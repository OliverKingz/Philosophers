/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:45:55 by ozamora-          #+#    #+#             */
/*   Updated: 2025/05/05 19:57:23 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_positive_nbr(const char *str)
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
	unsigned long	result;
	int				i;

	result = 0;
	i = 0;
	while (ft_isspace(*str))
		str++;
	if (str[i] == '+')
		i++;
	if (*str == '\0')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (UINT_MAX - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((unsigned int)result);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
