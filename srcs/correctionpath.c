/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correctionpath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:54:22 by damboule          #+#    #+#             */
/*   Updated: 2020/02/26 16:17:27 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			turnpath(t_salle *room, t_stack *find,
unsigned long stack, int begin)
{
	unsigned long	salle;
	unsigned long	tmp;
	int				index;

	salle = find->index_end;
	index = 0;
	while (salle != find->index_start)
	{
		tmp = room[stack].salle_prev[0];
		if (room[stack].salle_prev[0] != 0 && stack == find->index_start
		&& room[stack].salle_prev[0] != find->index_start)
			room[stack].liens->salle_prev = salle;
		else
			room[stack].salle_prev[0] = salle;
		index++;
		salle = stack;
		stack = tmp;
	}
	if (begin == 0)
		room[find->index_start].nb_salle = index;
	else if (begin == 1)
		room[find->index_start].liens->nb_salle = index;
}

void			mainturn(t_salle *room, t_stack *find)
{
	turnpath(room, find, room[find->index_end].salle_prev[0], 0);
	while (room[find->index_end].liens->salle_prev != 0)
	{
		turnpath(room, find, room[find->index_end].liens->salle_prev, 1);
		room[find->index_end].liens = room[find->index_end].liens->next;
		room[find->index_start].liens = room[find->index_start].liens->next;
	}
	room[find->index_end].liens = room[find->index_end].liens->begin;
	room[find->index_start].liens = room[find->index_start].liens->begin;
}

int				check_goals(unsigned long v_goals, t_salle *room,
unsigned long start)
{
	if (v_goals > (unsigned long)(room[start].ant_numb + room[start].nb_salle))
		return (v_goals);
	while (room[start].liens)
	{
		if ((room[start].liens->ant_numb + room[start].liens->nb_salle)
		> (room[start].ant_numb + room[start].nb_salle))
			return (room[start].liens->ant_numb + room[start].liens->nb_salle);
		if (room[start].liens->next == NULL)
			break ;
		room[start].liens = room[start].liens->next;
	}
	room[start].liens = room[start].liens->begin;
	return (v_goals + 1);
}

int				ft_break(int *len, int *clean, t_out **position)
{
	if ((*position)->next == NULL)
		return (1);
	if ((*position)->index == 0)
		(*len)--;
	if (*len == 0)
		*clean = 0;
	return (0);
}
