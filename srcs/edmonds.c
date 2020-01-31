/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 08:48:54 by damboule          #+#    #+#             */
/*   Updated: 2020/01/31 20:14:48 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	findpath(t_salle *room, t_stack *find, unsigned long end)
{
	int len;
	int index;

	len = 0;
	index = 0;
	//ft_printf("\n____________________________________\n");
	path(room, find, find->index_end, room[end].salle_prev[0]);
	while (room[end].liens->salle_prev != 0)
	{
		//ft_printf("\n\n");
		path(room, find, find->index_end, room[end].liens->salle_prev);
		if (room[end].liens->next == NULL)
			break ;
		room[end].liens = room[end].liens->next;
	}
	room[end].liens = room[end].liens->begin;
}

void	ft_clean_end(t_salle *room, t_stack *find)
{
	room[find->index_end].salle_prev[0] = 0;
	while (room[find->index_end].liens->salle_prev != 0)
	{
		room[find->index_end].liens->salle_prev = 0;
		if (room[find->index_end].liens->next == NULL)
			break ;
		room[find->index_end].liens = room[find->index_end].liens->next;
	}
	room[find->index_end].liens->salle_prev = 0;
	room[find->index_end].liens = room[find->index_end].liens->begin;
}

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
	if (v_goals > (room[end].ant_numb + room[end].nb_salle))
		return (v_goals);
	while (room[end].liens->salle_prev != 0)
	{
		if ((room[end].liens->ant_numb + room[end].liens->nb_salle) >
								(room[end].ant_numb + room[end].nb_salle))
		{
			room[end].liens = room[end].liens->begin;
			return (room[end].liens->ant_numb + room[end].liens->nb_salle);
		}
		room[end].liens = room[end].liens->next;
	}
	room[end].liens = room[end].liens->begin;
	return (v_goals + 1);
}

int		repart_eval(t_salle *room, t_stack *find, t_out *link, unsigned long ants)
{
	int		diff;
	
	printpath(room, find);
	diff = link->nb_salle;
	while (ants)
	{
		diff = get_diff(diff, room, find->index_end);
		room[find->index_end].ant_numb += 1;
		ants--;
		while (link->salle_prev != 0)
		{	
			if (diff > (link->ant_numb + link->nb_salle)
					&& ants && ants-- > 0)
				link->ant_numb += 1;
			link = link->next;
		}
		link = link->begin;
	}
	diff = room[find->index_end].ant_numb + room[find->index_end].nb_salle;
	clean_rep(room, find);
	return (diff);
}

int		bhandari(t_salle *room, t_stack *find, t_out *index)
{
	t_snapshot	*best_shot;
	t_snapshot	*current;
	t_banned	*banlink;

	shot_init(&best_shot);
	shot_init(&current);
	while (find->bhandari[0] < 1 && find->finish != 0)
	{
		algo(room, find, index);
		current->lines = repart_eval(room, find,
					room[find->index_end].liens->begin, find->fourmies);
		if (find->bhandari[0] == -1 && find->finish != 0)
		{
			ft_clean_end(room, find);
			ft_clean(room, index);
		}
	}
	return (1);
}
