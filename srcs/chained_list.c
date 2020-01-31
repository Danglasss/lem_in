/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:19:28 by dygouin           #+#    #+#             */
/*   Updated: 2020/01/31 21:34:43 by damboule         ###   ########.fr       */
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
	while (list != NULL && i++ > -1)
		list = list->next;
	return (i);
}

void	cpy_length(t_out **dst, t_out *src, t_out **begin)
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
	(*dst) = (*dst)->begin;
	(*begin) = (*begin)->begin;
}

void	banned_cpy(t_banned **dst, unsigned long room1, unsigned long room2)
{
	(*dst)->room1 = room1;
	(*dst)->room2 = room2;
	if ((*dst)->next == NULL)
		banned_add_tolist(dst, 0, 0);
	else
		(*dst) = (*dst)->next;
}

void	snapshot_cpy(t_snapshot **best, t_snapshot *curr)
{
	(*best)->lines = curr->lines;
	while (curr->banned)
	{
		(*best)->banned->room1 = curr->banned->room1;
		(*best)->banned->room2 = curr->banned->room2;
		if ((*best)->banned->next == NULL)
			banned_add_tolist(&(*best)->banned, 0, 0);
		else
			(*best)->banned = (*best)->banned->next;
		curr->banned = curr->banned->next;
	}
	(*best)->banned = (*best)->banned->begin;
}