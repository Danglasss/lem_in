/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:01:59 by danglass          #+#    #+#             */
/*   Updated: 2020/01/07 12:22:46 by danglass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	turnpath(t_salle *room, t_stack *find, unsigned long stack)
{
	unsigned long salle;
	unsigned long tmp;

	salle = find->index_end;
	while (salle != find->index_start)
	{
		ft_printf("salle == %s || stack == %s\n", room[salle].salle, room[stack].salle);
		tmp = room[stack].salle_prev[0];
		if (room[stack].salle_prev[0] != 0 && stack == find->index_start)
			room[stack].liens->salle_prev = salle;
		else
			room[stack].salle_prev[0] = salle;
		salle = stack;
		stack = tmp;
	}
}

void	mainturn(t_salle *room, t_stack *find)
{
	turnpath(room, find, room[find->index_end].salle_prev[0]);
	while (room[find->index_end].liens->salle_prev != 0)
	{
		turnpath(room, find, room[find->index_end].liens->salle_prev);
		room[find->index_end].liens = room[find->index_end].liens->next;
	}
	room[find->index_end].liens = room[find->index_end].liens->begin;
}

void	bfs_print(t_salle *room, t_stack *find, unsigned long salle)
{
	while (1)
	{
		if (salle == find->index_end)
		{
			return ;
		}
		if (room[salle].n_lem == 0)
		{
			return ;
		}
	}
}

void	affichage(t_salle *room, t_stack *find)
{
	int		total_fourmies;

	total_fourmies = find->fourmies;
	find->fourmies = 1;
	mainturn(room, find);
	while (room[find->index_end].n_lem == total_fourmies)
	{
		bfs_print(room, find, room[index_start].salle_prev[0])
		while (room[find->index_end].liens->salle_prev != 0)
		{
			bfs_print(room, find, room[index_start].liens->salle_prev[0])
			room[find->index_end].liens = room[find->index_end].liens->next;
		}
		room[find->index_end].liens = room[find->index_end].liens->begin;	
	}
}
