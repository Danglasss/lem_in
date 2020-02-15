/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkscondition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:19:23 by damboule          #+#    #+#             */
/*   Updated: 2020/02/15 18:43:13 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		same_path(t_salle *room, t_stack *find,
unsigned long index, unsigned long value)
{
	while (find->index_start != index)
	{
		if (index == value)
			return (1);
		index = room[index].salle_prev[1];
	}
	return (0);
}

int		stop_up(t_out *link, t_stack *find, t_salle *room, unsigned long index)
{
	link = link->begin;
	while (link)
	{
		if (link->open == 0 && find->index_start != (unsigned long)link->out)
			return (1);
		if (link->open == 3
				&& room[index].lenght < room[(unsigned long)link->out].lenght)
			return (1);
		if (link->next == NULL)
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
		if ((unsigned long)link->out ==
			room[index].salle_prev[1] || (unsigned long)link->out == 0)
		{
			if (link->next == NULL)
				break ;
			link = link->next;
			continue ;
		}
		if (((link->open == 0 && find->index_start != (unsigned long)link->out))
				|| (link->open == 1 && room[index].ascend == 0))
			return (1);
		if (link->next == NULL)
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
