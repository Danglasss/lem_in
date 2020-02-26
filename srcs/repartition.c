/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repartition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:13:15 by damboule          #+#    #+#             */
/*   Updated: 2020/02/26 16:19:42 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_rep(t_salle *room, t_stack *find)
{
	t_out *link;

	link = room[find->index_end].liens->begin;
	room[find->index_end].ant_numb = 0;
	room[find->index_end].nb_salle = 0;
	while (link)
	{
		link->ant_numb = 0;
		link->nb_salle = 0;
		if (link->next == NULL)
			break ;
		link = link->next;
	}
	link = link->begin;
}

int		get_diff(unsigned long v_goals, t_salle *room, unsigned long end)
{
	room[end].liens = room[end].liens->begin;
	if (v_goals > (unsigned long)(room[end].ant_numb + room[end].nb_salle))
		return (v_goals);
	while (room[end].liens->salle_prev != 0)
	{
		if ((room[end].liens->ant_numb + room[end].liens->nb_salle) >
			(room[end].ant_numb + room[end].nb_salle))
		{
			return (room[end].liens->ant_numb + room[end].liens->nb_salle);
		}
		room[end].liens = room[end].liens->next;
	}
	room[end].liens = room[end].liens->begin;
	return (v_goals + 1);
}

void	printrp(t_salle *room, t_stack *find)
{
	room[find->index_end].liens = room[find->index_end].liens->begin;
	while (1)
	{
		if (room[find->index_end].liens->next == NULL)
			break ;
		room[find->index_end].liens = room[find->index_end].liens->next;
	}
	room[find->index_end].liens = room[find->index_end].liens->begin;
}

void	crement_ants(unsigned long *nb_ants, int *pose_ants)
{
	*pose_ants += 1;
	*nb_ants -= 1;
}

int		repart_eval(t_salle *room, t_stack *find, t_out *link, t_path *current)
{
	int				diff;
	unsigned long	ants;

	diff = link->nb_salle;
	ants = find->fourmies;
	printpath(room, find, current);
	while (ants)
	{
		diff = get_diff(diff, room, find->index_end);
		if (diff > (room[find->index_end].ant_numb +
			room[find->index_end].nb_salle) && ants)
			crement_ants(&ants, &room[find->index_end].ant_numb);
		while (link->salle_prev != 0)
		{
			if (diff > (link->ant_numb + link->nb_salle)
					&& ants)
				crement_ants(&ants, &link->ant_numb);
			link = link->next;
		}
		link = link->begin;
	}
	diff = room[find->index_end].ant_numb + room[find->index_end].nb_salle;
	printrp(room, find);
	clean_rep(room, find);
	return (diff);
}
