/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dygouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:52:06 by dygouin           #+#    #+#             */
/*   Updated: 2020/02/06 13:55:05 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/lem_in.h"

void	outn_prev(t_out **out, unsigned int n)
{
	unsigned int	count;

	count = 0;
	while (count++ < n)
		(*out) = (*out)->prev;
}

int		len_out(t_out *list, int origin)
{
	int		i;

	i = 0;
	if (origin == 1)
		list = list->begin;
	while (list->next != NULL && i++ > -1)
		list = list->next;
	return (i + 1);
}
