/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:01:59 by danglass          #+#    #+#             */
/*   Updated: 2020/01/07 23:26:51 by danglass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	turnpath(t_salle *room, t_stack *find, unsigned long stack, int begin)
{
	unsigned long	salle;
	unsigned long	tmp;
	int				index;

	salle = find->index_end;
	index = 0;
	while (salle != find->index_start)
	{
		ft_printf("salle == %s || stack == %s\n", room[salle].salle, room[stack].salle);
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

void	mainturn(t_salle *room, t_stack *find)
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

int		check_goals(unsigned long v_goals, t_salle *room, unsigned long start)
{
	if (v_goals > (room[start].ant_numb + room[start].nb_salle))
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

void	repartition(t_salle *room, t_stack *find, unsigned long v_goals, int ants)
{
	while (ants != 0)
	{
		v_goals = check_goals(v_goals, room, find->index_start);
		room[find->index_start].ant_numb += 1;
		ants -= 1;
		room[find->index_start].liens = room[find->index_start].liens->begin;
		while (room[find->index_start].liens)
		{
			if (v_goals > 
			(room[find->index_start].liens->ant_numb + room[find->index_start].liens->nb_salle)
			&& ants > 0 && room[find->index_start].liens->salle_prev != 0)
			{
				room[find->index_start].liens->ant_numb += 1;
				ants -= 1;
			}
			if (room[find->index_start].liens->next == NULL)
				break ;
			room[find->index_start].liens = room[find->index_start].liens->next;
		}
		room[find->index_start].liens = room[find->index_start].liens->begin;
	}
}

unsigned long	put_ant(t_salle *room, t_stack *find, int pose, unsigned long salle)
{
	unsigned long num;

	if (pose == 0)
		return (room[salle].n_lem);
	if (room[salle].n_lem == 0 && room[room[salle].salle_prev[0]].n_lem == 0)
		pose = 0;
	room[salle].n_lem = find->fourmies;
	num = room[salle].n_lem;
	find->fourmies += 1;
	ft_printf(" L%d-%s ", room[salle].n_lem, room[salle].salle);
	if (pose == 0)
		return (0);
	return (num);
}

void	print_graph(t_salle *room, t_stack *find, unsigned long salle, int pose)
{
	unsigned long num;
	unsigned long tmp;

	if ((num = put_ant(room, find, pose, salle)) == 0)
		return ;
	salle = room[salle].salle_prev[0];
	while (salle != find->index_end)
	{
		if (room[salle].n_lem != 0 || num != 0)
		{
			tmp = room[salle].n_lem;
			room[salle].n_lem = num;
			if (room[salle].n_lem != 0)
				ft_printf(" L%d-%s", room[salle].n_lem, room[salle].salle);
			num = tmp;
		}
		salle = room[salle].salle_prev[0];
	}
	if (num != 0)
	{
		room[find->index_end].n_lem += 1;
		ft_printf(" L%d-%s", num, room[salle].salle);
	}
}

void	affichage(t_salle *room, t_stack *find)
{
	int max_fourmies;
	int ants;
	int pose;

	ants = 1;
	pose = 0;
	max_fourmies = find->fourmies;
	find->fourmies = 1;
	mainturn(room, find);
	repartition(room, find, room[find->index_start].liens->nb_salle, find->fourmies);
	while (room[find->index_end].n_lem < max_fourmies)
	{
		pose = 0;
		if (room[find->index_start].ant_numb > 0)
		{
			room[find->index_start].ant_numb--;
			pose = 1;
		}
		print_graph(room, find, room[find->index_start].salle_prev[0], pose);
		while (room[find->index_start].liens)
		{
			pose = 0;
			if (room[find->index_start].liens->ant_numb > 0)
			{
				room[find->index_start].liens->ant_numb--;
				pose = 1;
			}
			if (room[find->index_start].liens->salle_prev != 0)
				print_graph(room, find, room[find->index_start].liens->salle_prev, find->index_start);
			if (room[find->index_start].liens->next == NULL)
				break ;
			room[find->index_start].liens = room[find->index_start].liens->next;
		}
		ft_printf("\n");
		room[find->index_start].liens = room[find->index_start].liens->begin;
	}
}
