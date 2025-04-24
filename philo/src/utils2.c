/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:45:55 by ozamora-          #+#    #+#             */
/*   Updated: 2025/04/24 16:00:08 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] == '\f' || nptr[i] == '\n' || nptr[i] == '\r'
		|| nptr[i] == '\t' || nptr[i] == '\v' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (sign * res);
}

int	check_args_int(char **args)
{
	int	i;

	if (args == NULL || *args == NULL)
		return (0);
	i = 0;
	while (args[i] != NULL)
	{
		if (!ft_issigned_nbr(args[i]))
			return (0);
		if (my_str_num_len(args[i]) > 10)
			return (0);
		i++;
	}
	return (1);
}

int	my_str_num_len(char *str_num)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (str_num[i] == '-' || str_num[i] == '+')
	{
		i++;
	}
	while (str_num[i] == '0')
	{
		i++;
	}
	while (str_num[i] >= '0' && str_num[i] <= '9')
	{
		len++;
		i++;
	}
	return (len);
}

int	*my_strarray_to_intarray(char **str)
{
	int		num_strs;
	int		i;
	int		*int_array;
	long	value;

	if (str == NULL || *str == NULL)
		return (NULL);
	num_strs = 0;
	while (str[num_strs] != NULL)
		num_strs++;
	int_array = (int *)ft_calloc(num_strs, sizeof(int));
	if (!int_array)
		return (NULL);
	i = 0;
	while (i < num_strs)
	{
		value = ft_atol(str[i]);
		if (value > INT_MAX || value < INT_MIN || my_str_num_len(str[i]) > 10)
			return (free(int_array), NULL);
		int_array[i] = (int)value;
		i++;
	}
	return (int_array);
}

int	ft_issigned_nbr(const char *str)
{
	if (str == NULL)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	while (ft_isspace(*str))
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}
