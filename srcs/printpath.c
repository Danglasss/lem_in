/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:58:39 by damboule          #+#    #+#             */
/*   Updated: 2020/02/07 17:48:16 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		p_salle(t_salle *room, t_stack *find, unsigned long salle_prev, t_cases *current)
{
	unsigned long	index;
	unsigned long	tmp;
	int				len;

	index = find->index_end;
	len = 0;
	while (index != find->index_start)
	{
		cases_add_tolist(&current, index);
		len++;
		if (index == find->index_end)
		{
			index = salle_prev;
			continue ;
		}
		index = room[index].salle_prev[0];
	}
	cases_add_tolist(&current, index);
	return (len);
}

void	printpath(t_salle *room, t_stack *find, t_path *current)
{
	int				curr;
	unsigned long	end;
	int				len;
	int				index;
	
	end = find->index_end;
	curr = 0;
	index = 1;
	len = p_salle(room, find, room[end].salle_prev[0], current[curr].cases->begin);
	room[end].nb_salle = len;
	room[end].liens = room[end].liens->begin;
	while (room[end].liens->salle_prev != 0)
	{
		curr++;
		index++;
		len = p_salle(room, find, room[end].liens->salle_prev, current[curr].cases->begin);
		room[end].liens->nb_salle = len;
		if (room[end].liens->next == NULL)
			break ;
		room[end].liens = room[end].liens->next;
	}
	room[end].liens = room[end].liens->begin;
}
