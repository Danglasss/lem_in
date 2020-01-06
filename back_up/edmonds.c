/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 08:48:54 by damboule          #+#    #+#             */
/*   Updated: 2019/12/24 12:31:34 by danglass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int			ft_add_way(t_pos **pos, int colle)
{
	pos_add_tolist(pos, NULL, 1);
	(*pos)->id = len_pos(*pos, 1);
	(*pos)->colle = colle;
	return (1);
}

void		ft_index(t_pos *pos, long long *prev_index, long long *t_index,
			int *count)
{
	if (pos->ways->prev != NULL)
		*prev_index = (unsigned long)pos->ways->prev->out;
	else
		*prev_index = -1;
	if (pos->ways->out != NULL)
		*t_index = (unsigned long)pos->ways->out;
	else
		*t_index = (unsigned long)pos->ways->prev->out;
	*count = 0;
}

void		ft_bfs(t_salle *room, t_stack *find, t_pos *pos, t_pos *path)
{
	unsigned long		n_path;
	int					tmp;

	n_path = len_pos(pos, 1);
	tmp = len_pos(pos, 1);
	pos->id = 1;
	while (n_path-- && path->ways != NULL && pos != NULL)
	{
		ft_main_bfs(room, find, pos, path);
		find->lenght += 1;
		pos = pos->next;
		if (pos != NULL && tmp < len_pos(pos, 1))
		{
			while (tmp < len_pos(pos, 1))
			{
				tmp = tmp + 1;
				if (pos->next != NULL)
					pos = pos->next;
			}
		}
	}
}

void		ft_pathfirst(t_salle *room, t_stack *find, t_pos *pos, t_pos *path)
{
	while (find->result == 0)
	{
		ft_bfs(room, find, pos, path);
		pos = pos->begin;
	}
}

void		ft_clear(t_salle *room, int valide, t_pos *pos)
{
	pos = pos->begin;
	while (pos != NULL)
	{
		pos->ways = pos->ways->begin;
		while (pos->ways != NULL)
		{
			if (valide == 0 || valide == 2)
				room[(unsigned long)pos->ways->out].path = 0;
			if (valide == 1)
				room[(unsigned long)pos->ways->out].path = 1;
			if (pos->ways->next == NULL)
				break ;
			pos->ways = pos->ways->next;
		}
		if (pos->next == NULL)
			break ;
		pos = pos->next;
	}
	if (valide == 0)
		leaks_pos(pos);
}

void		ft_clear_data(t_pos *pos)
{
	pos = pos->begin;
	while (pos != NULL)
	{
		pos->instruction = 0;
		pos->fourmies = 0;
		if (pos->next == NULL)
			break ;
		pos = pos->next;
	}
}

void		ft_reset(t_stack *find, t_pos **pos, unsigned int *max)
{
	*max = 0;
	find->result = 0;
	find->espoir = 1;
	pos_init(pos, 0);
}

int			ft_saturation(t_salle *room, t_stack *find, int a)
{
	unsigned int index;

	if (a == 0)
		return (1);
	index = find->index_start;
	room[index].liens = room[index].liens->begin;
	while (room[index].liens != NULL)
	{
		if (room[(unsigned int)room[index].liens->out].path == 0 &&
		room[(unsigned int)room[index].liens->out].salle != NULL)
			return (1);
		if (room[index].liens->next == NULL)
			break ;
		room[index].liens = room[index].liens->next;
	}
	return (0);
}

int			ft_edmonds(t_salle *room, t_stack *find, t_pos *pos, t_pos *path)
{
	int						a;
	unsigned int			t_instruct;
	unsigned int			max_instruct;

	a = 0;
	find->espoir = 1; 
	find->lenght = 0;
	ft_set_reset(room, find, pos, path);
	ft_pathfirst(room, find, pos, path);
	find->result = 0;
	max_instruct = 0;
	while (ft_saturation(room, find, a))
	{
		a = 1;
		t_instruct = f_equal(path, find->fourmies - f_repartition(path));
		while (max_instruct < t_instruct)
		{
			ft_bfs(room, find, pos, path);
			if (find->result == 1)
			{
				t_instruct = f_equal(path, find->fourmies - f_repartition(path));
				find->result = 0;
			}
			max_instruct++;
			pos = pos->begin;
		}
	}
	ft_clear(room, 2, path);
	return (1);
}
