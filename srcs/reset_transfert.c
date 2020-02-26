/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_transfert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 10:16:23 by damboule          #+#    #+#             */
/*   Updated: 2020/02/26 16:19:52 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	transfert_true(t_salle *room, t_stack *find, unsigned long salle)
{
	while (find->index_start != salle)
	{
		room[salle].salle_prev[0] = room[salle].salle_prev[1];
		room[salle].salle_prev[1] = 0;
		room[salle].uses = 1;
		salle = room[salle].salle_prev[0];
	}
}

void	clear(t_salle *room, t_out *index)
{
	int len;

	index = index->begin;
	len = len_out(index, 1) - 1;
	while (len)
	{
		room[(unsigned long)index->out].free = 0;
		room[(unsigned long)index->out].ascend = 0;
		room[(unsigned long)index->out].lenght = 0;
		len = len - 1;
		index = index->next;
	}
}

void	ft_clean(t_salle *room, t_out *index)
{
	int len_room;

	index = index->begin;
	len_room = len_out(index, 1) - 1;
	while (len_room)
	{
		room[(unsigned long)index->out].liens =
		room[(unsigned long)index->out].liens->begin;
		room[(unsigned long)index->out].uses = 0;
		while (room[(unsigned long)index->out].liens)
		{
			room[(unsigned long)index->out].liens->open = 0;
			if (room[(unsigned long)index->out].liens->next == NULL)
				break ;
			else
				room[(unsigned long)index->out].liens =
				room[(unsigned long)index->out].liens->next;
		}
		room[(unsigned long)index->out].liens =
		room[(unsigned long)index->out].liens->begin;
		index = index->next;
		len_room--;
	}
	index = index->begin;
}

void	ft_reset(t_salle *room, t_out *index)
{
	int len_room;

	index = index->begin;
	len_room = len_out(index, 1) - 1;
	while (len_room-- > 0)
	{
		room[(unsigned long)index->out].liens =
		room[(unsigned long)index->out].liens->begin;
		while (room[(unsigned long)index->out].liens)
		{
			room[(unsigned long)index->out].liens->del[1] = 0;
			room[(unsigned long)index->out].salle_prev[1] = 0;
			if (room[(unsigned long)index->out].liens->next == NULL)
				break ;
			else
				room[(unsigned long)index->out].liens =
				room[(unsigned long)index->out].liens->next;
		}
		room[(unsigned long)index->out].liens =
		room[(unsigned long)index->out].liens->begin;
		index = index->next;
	}
	index = index->begin;
}

void	main_reset(t_salle *room, t_stack *find, t_out *index)
{
	if (find->finish == 1 && find->bhandari[0] != -1)
		findpath(room, find, find->index_end);
	clear(room, index);
	if (find->bhandari[0] != -1)
		find->bhandari[0] += finish(room, find);
	ft_reset(room, index);
}
