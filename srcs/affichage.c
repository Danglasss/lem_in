/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:01:59 by danglass          #+#    #+#             */
/*   Updated: 2020/01/07 18:23:39 by damboule         ###   ########.fr       */
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
		if (room[stack].salle_prev[0] != 0 && stack == find->index_start
		&& room[stack].salle_prev[0] != find->index_start)
		{
			room[stack].liens->salle_prev = salle;
			if (room[stack].liens->next != NULL)
				room[stack].liens = room[stack].liens->next;
		}
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
	room[find->index_start].liens = room[find->index_start].liens->begin;
}

void	bfs_print(t_salle *room, t_stack *find, unsigned long salle)
{
	int		index;
	int		tmp;
	int		stack;
	
	index = 0;
	while (salle != find->index_end)
	{
		if (room[salle].n_lem == 0)
		{
			room[salle].n_lem = find->fourmies;
			ft_printf(" L%d-%s ", find->fourmies, room[salle].salle);
			if (index == 0)
				find->fourmies += 1;
			return ;
		}
		else if (index == 0)
		{
			tmp = room[salle].n_lem;
			ft_printf(" L%d-%s ", find->fourmies, room[salle].salle);
			find->fourmies += 1;
			salle = room[salle].salle_prev[0];
			index++;			
			continue ;
		}
		else
		{
			stack = room[salle].n_lem;
			room[salle].n_lem = tmp;
			ft_printf(" L%d-%s ", tmp, room[salle].salle);
			salle = room[salle].salle_prev[0];
			tmp = stack;
		}
		index++;
	}
	ft_printf(" L%d-%s ", tmp, room[salle].salle);
	room[salle].n_lem += 1;
}

void	affichage(t_salle *room, t_stack *find)
{
	int		total_fourmies;

	total_fourmies = find->fourmies;
	find->fourmies = 1;
	mainturn(room, find);
	while (room[find->index_end].n_lem < total_fourmies)
	{
		bfs_print(room, find, room[find->index_start].salle_prev[0]);
		room[find->index_start].liens = room[find->index_start].liens->begin;	
		while (room[find->index_start].liens->salle_prev != 0)
		{
			bfs_print(room, find, room[find->index_start].liens->salle_prev);
			room[find->index_start].liens = room[find->index_start].liens->next;
		}
		//exit(1);
		ft_printf(" \n");
		room[find->index_start].liens = room[find->index_start].liens->begin;	
	}
}
