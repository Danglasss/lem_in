/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:30:37 by nabboufe          #+#    #+#             */
/*   Updated: 2019/09/18 17:31:30 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		check_l(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i] == '0')
		i++;
	if (ft_strlen(&str[i]) > 11)
		return (0);
	return (1);
}

long	ft_atoi_check(char *str)
{
	int		i;
	long	result;
	long	sign;

	i = 0;
	result = 0;
	sign = 1;
	if (!check_l(str))
		return (2147483648);
	if ((str[i] == '+' || str[i] == '-') && (i = 1))
	{
		if (str[i] == '-')
			sign = -1;
	}
	while (str[i])
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	result *= sign;
	if (result < -2147483648)
		return (2147483648);
	return (result);
}

size_t	ft_strtab(char **str)
{
	size_t i;

	i = 0;
	if (str == NULL || (!(str)))
		return (i);
	while (str[i] != 0)
		i++;
	return (i);
}

int		is_int(char *isint)
{
	long	number;

	number = ft_atoi_check(isint);
	if (number > 2147483647 || number < -2147483648)
		return (0);
	return (1);
}

int		is_number(char *string, int check_if_int)
{
	int		i;

	i = 0;
	if (string[i] == '+' || string[i] == '-')
		i++;
	if (!string[i])
		return (0);
	while (string[i])
	{
		if (string[i] < 48 || string[i] > 57)
			return (0);
		i++;
	}
	if (check_if_int == 1 && !is_int(string))
		return (0);
	return (1);
}
