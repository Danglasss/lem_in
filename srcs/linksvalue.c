/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linksvalue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 09:17:41 by damboule          #+#    #+#             */
/*   Updated: 2020/02/26 16:18:58 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	positif_link(t_salle *room, unsigned long index, t_stack *find)
{
	if (index == find->index_start)
		return ;
	room[index].liens = room[index].liens->begin;
	while ((unsigned long)room[index].liens->out != room[index].salle_prev[0])
		room[index].liens = room[index].liens->next;
	if ((unsigned long)room[index].liens->out !=
		find->index_end && (unsigned long)room[index].liens->out !=
		find->index_start)
		room[index].liens->open = 1;
}

void	negatif_link(t_salle *room, unsigned long index, unsigned long tmp)
{
	room[index].liens = room[index].liens->begin;
	while ((unsigned long)room[index].liens->out != tmp)
		room[index].liens = room[index].liens->next;
	room[index].liens->open = -1;
}

void	lucky_link(t_salle *room, unsigned long index, unsigned long tmp)
{
	room[index].liens = room[index].liens->begin;
	while ((unsigned long)room[index].liens->out != tmp)
	{
		if (room[index].liens->next == NULL)
			break ;
		room[index].liens = room[index].liens->next;
	}
	room[index].liens->open = 3;
	room[index].liens = room[index].liens->begin;
}

void	neutral_link(t_salle *room, unsigned long index, unsigned long tmp)
{
	if (len_out(room[index].liens, 1) < 3)
		return ;
	room[index].liens = room[index].liens->begin;
	while (room[index].liens != NULL)
	{
		if ((unsigned long)room[index].liens->out != tmp &&
				(unsigned long)room[index].liens->out !=
				room[index].salle_prev[0]
				&& (unsigned long)room[index].liens->out != 0)
		{
			lucky_link(room, (unsigned long)room[index].liens->out, index);
			room[index].liens->open = 3;
		}
		if (room[index].liens->next == NULL)
			break ;
		room[index].liens = room[index].liens->next;
	}
	room[index].liens = room[index].liens->begin;
}

void	path(t_salle *room, t_stack *find, unsigned long salle_prev)
{
	unsigned long index;
	unsigned long tmp;

	index = find->index_end;
	while (index != find->index_start)
	{
		if (index != find->index_end)
		{
			negatif_link(room, index, tmp);
			positif_link(room, index, find);
			neutral_link(room, index, tmp);
		}
		tmp = index;
		if (index == find->index_end)
		{
			index = salle_prev;
			continue ;
		}
		index = room[index].salle_prev[0];
	}
	negatif_link(room, index, tmp);
	positif_link(room, index, find);
}
