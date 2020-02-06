/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_primes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dygouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:26:31 by dygouin           #+#    #+#             */
/*   Updated: 2020/02/06 12:26:38 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int				is_prime(unsigned long number)
{
	unsigned int	i;

	i = 2;
	if (number == 2)
		return (1);
	while (i < number)
	{
		if (number % i == 0)
			return (0);
		i++;
	}
	return (1);
}

unsigned long	n_prime(unsigned long l_number)
{
	l_number *= 1223;
	while (!is_prime(l_number))
		l_number++;
	return (l_number);
}
