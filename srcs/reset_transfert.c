/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_transfert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 10:16:23 by damboule          #+#    #+#             */
/*   Updated: 2020/01/28 15:05:42 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	transfert_true(t_salle *room, t_stack *find, unsigned long salle)
{
	while (find->index_start != salle)
	{
		room[salle].salle_prev[0] = room[salle].salle_prev[1];
		room[salle].salle_prev[1] = 0;
		salle = room[salle].salle_prev[0];
	}
}

void	clear(t_salle *room, t_stack *find, t_out *index)
{
	int len;

	index = index->begin;
	len = len_out(index, 1) - 1;
	while (len)
	{
		room[(unsigned long)index->out].free = 0;
		len = len - 1;
		index = index->next;
	}
}

void	ft_clean(t_salle *room, t_out *index)
{
	int len_room;
	int len_lien;

	index = index->begin;
	len_room = len_out(index, 1) - 1;
	while (len_room)
	{
		len_lien = len_out(room[(unsigned long)index->out].liens, 1) - 1;
		room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->begin;
		while (len_lien)
		{
			room[(unsigned long)index->out].liens->open = 0;
			if (room[(unsigned long)index->out].liens->next == NULL)
				len_lien = 0;
			else
				room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->next;
		}
		room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->begin;
		index = index->next;
		len_room--;
	}
	index = index->begin;
}

void	ft_reset(t_salle *room, t_out *index)
{
	int len_room;
	int len_lien;

	index = index->begin;
	len_room = len_out(index, 1) - 1;
	while (len_room)
	{
		len_lien = len_out(room[(unsigned long)index->out].liens, 1) - 1;
		room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->begin;
		while (len_lien)
		{
			room[(unsigned long)index->out].liens->del[1] = 0;
			room[(unsigned long)index->out].salle_prev[1] = 0;
			if (room[(unsigned long)index->out].liens->next == NULL)
				len_lien = 0;
			else
				room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->next;
		}
		room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->begin;
		index = index->next;
		len_room--;
	}
	index = index->begin;
}