/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:19:28 by dygouin           #+#    #+#             */
/*   Updated: 2020/01/30 15:04:51 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/lem_in.h"

void	posn_prev(t_pos **pos, unsigned int n)
{
	unsigned int	count;

	count = 0;
	while (count++ < n)
		(*pos) = (*pos)->prev;
}

void	outn_prev(t_out **out, unsigned int n)
{
	unsigned int	count;

	count = 0;
	while (count++ < n)
		(*out) = (*out)->prev;
}

int		len_pos(t_pos *list, int origin)
{
	int	i;

	i = 0;
	if (origin == 1)
		list = list->begin;
	while (list != NULL && i++ > -1)
		list = list->next;
	return (i);
}

int		len_out(t_out *list, int origin)
{
	int		i;

	i = 0;
	//ft_printf("44\n");
	if (origin == 1)
		list = list->begin;
	while (list != NULL && i++ > -1)
	{
		//ft_printf("55\n");
		list = list->next;
		//ft_printf("66\n");
	}
	return (i);
}

void	cpy_length(t_out **dst, t_out *src)
{
	(*dst) = (*dst)->begin;
	src = src->begin;
	while (src && (*dst))
	{
		(*dst)->index = src->index;
		src->index = 0;
		if ((*dst)->next == NULL)
			out_add_tolist(dst, NULL, 1);
		else
			(*dst) = (*dst)->next;
		src = src->next;
	}
}
