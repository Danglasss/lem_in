/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:41:22 by damboule          #+#    #+#             */
/*   Updated: 2020/01/31 10:00:32 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		ft_delcheck(unsigned long path, t_salle *room, t_stack *find)
{
	while (room[path].liens)
	{
		if (room[path].liens->del[1] == 1 /*&& (unsigned long)room[path].liens->out == s_room*/)
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

int		ft_check(unsigned long path, unsigned long salle, t_stack *find, t_salle *room)
{	
	while (path != find->index_start)
	{
		if (path == salle && ft_delcheck(path, room, find)) // also check if lien del
			return (1);
		path = room[path].salle_prev[0];
	}
	return (0);
}

void	permanant_delink(t_salle *room, t_stack *find, unsigned long index)
{
	find->bhandari[1] = 0;
	find->bhandari[0] = -1;
	while (index != find->index_start)
	{
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

int		verify_colision(t_salle *room, unsigned long salle, t_stack *find)
{
	unsigned long index;
	unsigned long end;
	
	index = salle;
	end = find->index_end;
	while (index != find->index_start)
	{
		if (find->bhandari[0] == -1)
			break ;
		if (ft_check(room[end].salle_prev[0], index, find, room))
			return (0);
		while (room[end].liens->salle_prev != 0)
		{
			if (ft_check(room[end].liens->salle_prev, index, find, room))
				return (0);
			if (find->bhandari[0] == -1)
				break ;
			room[end].liens = room[end].liens->next;
		}
		if (find->bhandari[0] == -1)
			break ;
		room[end].liens = room[end].liens->begin;
		index = room[index].salle_prev[1];
	}
	if (find->bhandari[1] == -1)
		permanant_delink(room, find, salle);
	return (1);
}

int		suplink(t_out *link, t_stack *find)
{
	link = link->begin;
	while (link)
	{
		if ((link->open == 1) && find->index_start != (unsigned long)link->out)
			return (1);
		if (link->next  == NULL)
			break ;
		link = link->next;
	}
	link = link->begin;
	return (0);
}

int		toplink(t_out *link, t_stack *find, t_salle *room, unsigned long index)
{
	link = link->begin;
	while (link)
	{
		if ((unsigned long)link->out == room[index].salle_prev[1] || (unsigned long)link->out == 0)
		{
			if (link->next == NULL)
				break ;
			link = link->next;
			continue ;
		}
		if (((link->open == 0 && find->index_start != (unsigned long)link->out))
				|| (link->open == 1 && room[index].ascend == 0))
			return (1);
		if (link->next  == NULL)
			break ;
		link = link->next;
	}
	link = link->begin;
	return (0);
}

int		finish(t_salle *room, t_stack *find, t_out *index)
{
	int				len;
	int				lenght;

	if (room[find->index_end].salle_prev[0] != 0)
		len = 1;
	lenght = len_out(room[find->index_end].liens, 1) - 1;
	while (room[find->index_end].liens)
	{
		if (room[find->index_end].liens->open == -1)
			len++;
		else if (room[find->index_end].liens->salle_prev != 0)
			len++;
		if (lenght == len)
			return (1);
		if (room[find->index_end].liens->next == NULL)
			break ;
		room[find->index_end].liens = room[find->index_end].liens->next;
	}
	room[find->index_end].liens = room[find->index_end].liens->begin;
	return (0);
}