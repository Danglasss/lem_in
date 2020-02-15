/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:01:59 by danglass          #+#    #+#             */
/*   Updated: 2020/02/15 19:23:30 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void			repartition(t_salle *room, t_stack *find,
unsigned long v_goals, int ants)
{
	while (ants != 0)
	{
		v_goals = check_goals(v_goals, room, find->index_start);
		room[find->index_start].ant_numb += 1;
		ants -= 1;
		room[find->index_start].liens = room[find->index_start].liens->begin;
		while (room[find->index_start].liens)
		{
			if (v_goals > (room[find->index_start].liens->ant_numb +
				room[find->index_start].liens->nb_salle)
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

unsigned long	put_ant(t_salle *room, t_stack *find,
unsigned long salle, int *ants)
{
	unsigned long num;

	num = 0;
	if (*ants > 0 && (room[salle].n_lem == 0 || room[salle].n_lem > 0))
	{
		num = room[salle].n_lem;
		room[salle].n_lem = find->fourmies;
		ft_printf("L%d-%s ", room[salle].n_lem, room[salle].salle);
		*ants -= 1;
		find->fourmies += 1;
		return (num);
	}
	else if (*ants == 0 && (room[salle].n_lem > 0 || room[salle].n_lem == 0))
	{
		num = room[salle].n_lem;
		if (room[salle].n_lem == 0)
			num = 0;
		room[salle].n_lem = 0;
		return (num);
	}
	return (num);
}

void			print_graph(t_salle *room, t_stack *find,
unsigned long salle, unsigned long num)
{
	unsigned long stack;

	while (salle != find->index_end)
	{
		stack = room[salle].n_lem;
		room[salle].n_lem = num;
		if (room[salle].n_lem != 0)
			ft_printf("L%d-%s ", room[salle].n_lem, room[salle].salle);
		num = stack;
		salle = room[salle].salle_prev[0];
	}
	if (num != 0)
	{
		ft_printf("L%d-%s ", num, room[salle].salle);
		room[find->index_end].n_lem += 1;
	}
}

void			browse_graph(t_salle *room, t_stack *find, unsigned long s)
{
	unsigned long		num;
	unsigned long		total_ants;

	total_ants = find->fourmies;
	find->fourmies = 1;
	while (total_ants != room[find->index_end].n_lem)
	{
		num = put_ant(room, find, room[s].salle_prev[0], &room[s].ant_numb);
		print_graph(room, find, room[room[s].salle_prev[0]].salle_prev[0], num);
		room[s].liens = room[s].liens->begin;
		while (room[s].liens)
		{
			num = put_ant(room, find,
			room[s].liens->salle_prev, &room[s].liens->ant_numb);
			if (room[s].liens->salle_prev != 0)
				print_graph(room, find,
					room[room[s].liens->salle_prev].salle_prev[0], num);
			if (room[s].liens->next == NULL)
				break ;
			room[s].liens = room[s].liens->next;
		}
		room[s].liens = room[s].liens->begin;
		ft_printf("\n");
	}
}

void			affichage(t_salle *room, t_stack *find)
{
	int		i;

	i = 0;
	mainturn(room, find);
	repartition(room, find, room[find->index_start].liens->nb_salle,
	find->fourmies);
	if (room[find->index_start].salle_prev[0] == find->index_end)
	{
		while (i <= find->fourmies)
		{
			ft_printf("L%d-%s ", i, room[find->index_end].salle);
			i++;
		}
		ft_printf("\n");
		return ;
	}
	browse_graph(room, find, find->index_start);
}
