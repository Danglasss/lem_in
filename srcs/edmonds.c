/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 08:48:54 by damboule          #+#    #+#             */
/*   Updated: 2020/01/30 15:36:05 by damboule         ###   ########.fr       */
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


void	repart_eval(t_salle *room, t_stack *find)
{
	int		diff;
	t_out	*link;

	while (1)
	{
		link = room[find->index_end].liens;
		if (link->next == NULL)
			break ;
		diff = link->next->nb_salle - link->nb_salle;
		link->ant_numb = diff;
		while (link)
		{	
			if (link->next == NULL)
				break ;
			diff = link->next->nb_salle - link->nb_salle;
			link->ant_numb = diff;
			link = link->next;
		}
	}
}

int		bhandari(t_salle *room, t_stack *find, t_out *index)
{

	while (find->bhandari[0] < 1)
	{
		find->finish = 0;
		find->bhandari[0] = 0;
		algo(room, find, index);
		//printpath(room, find);
		//repart_eval(room, find);
		if (find->finish == 0)
			break ;
		if (find->bhandari[0] == -1)
		{
			ft_clean_end(room, find);
			ft_clean(room, index);
		}
	}
	return (1);
}