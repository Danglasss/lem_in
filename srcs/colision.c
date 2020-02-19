/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:41:22 by damboule          #+#    #+#             */
/*   Updated: 2020/02/19 11:27:39 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	permanant_delink(t_salle *room, t_stack *find, unsigned long index)
{
	find->bhandari[1] = 0;
	find->bhandari[0] = -1;
	while (index != find->index_start)
	{
		room[index].liens = room[index].liens->begin;
		while (room[index].liens)
		{
			if (room[index].liens->del[1] == 1)
			{
				room[index].liens->del[0] = room[index].liens->del[1];
				room[index].liens->del[1] = 0;
			}
			if (room[index].liens->next == NULL)
				break ;
			room[index].liens = room[index].liens->next;
		}
		room[index].liens = room[index].liens->begin;
		index = room[index].salle_prev[1];
	}
}

int		ft_delcheck(unsigned long path, t_salle *room, t_stack *find,
			unsigned long s_room[2])
{
	while (room[path].liens)
	{
		if (room[path].liens->del[1] == 1 &&
			((unsigned long)room[path].liens->out == s_room[0] ||
			(unsigned long)room[path].liens->out == s_room[1]))
		{
			find->bhandari[1] = -1;
			room[path].liens = room[path].liens->begin;
			return (0);
		}
		if (room[path].liens->next == NULL)
			break ;
		room[path].liens = room[path].liens->next;
	}
	room[path].liens = room[path].liens->begin;
	return (1);
}

int		ft_check(unsigned long path, unsigned long salle[2],
				t_stack *find, t_salle *room)
{
	unsigned long s_room[2];

	s_room[0] = room[salle[0]].salle_prev[1];
	s_room[1] = salle[1];
	while (path != find->index_start)
	{
		if (path == salle[0] && ft_delcheck(path, room, find, s_room))
		{
			find->bhandari[1] = 0;
			return (1);
		}
		path = room[path].salle_prev[0];
	}
	return (0);
}

int		verify_colision(t_salle *room, unsigned long salle, t_stack *find)
{
	unsigned long index[2];
	unsigned long end;

	index[0] = salle;
	end = find->index_end;
	while (index[0] != find->index_start)
	{
		if (ft_check(room[end].salle_prev[0], index, find, room))
			return (0);
		while (room[end].liens->salle_prev != 0)
		{
			if (ft_check(room[end].liens->salle_prev, index, find, room))
				return (0);
			room[end].liens = room[end].liens->next;
		}
		room[end].liens = room[end].liens->begin;
		index[1] = index[0];
		index[0] = room[index[0]].salle_prev[1];
	}
	if (find->bhandari[1] == -1)
		permanant_delink(room, find, salle);
	return (1);
}

void	delete_link(t_out **liens, t_salle *room, unsigned long salle)
{
	int len;

	(*liens)->del[1] = 1;
	room[(unsigned long)(*liens)->out].ascend = 1;
	room[(unsigned long)(*liens)->out].liens =
	room[(unsigned long)(*liens)->out].liens->begin;
	len = len_out(room[(unsigned long)(*liens)->out].liens, 1) - 1;
	while ((unsigned long)room[(unsigned long)(*liens)->out].liens->out !=
		salle)
	{
		room[(unsigned long)(*liens)->out].liens =
		room[(unsigned long)(*liens)->out].liens->next;
		len--;
	}
	room[(unsigned long)(*liens)->out].liens->del[1] = 1;
	room[(unsigned long)(*liens)->out].liens =
	room[(unsigned long)(*liens)->out].liens->begin;
}
