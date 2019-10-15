/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 08:48:54 by damboule          #+#    #+#             */
/*   Updated: 2019/10/12 02:43:54 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int			ft_add_way(t_pos **pos)
{
	pos_add_tolist(pos, NULL, 1);
	(*pos)->id = len_pos(*pos, 1);
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
	unsigned long		start;

	start = t_hash(find->n_start, room);
	find->ways = 0;
	find->result = 0;
	pos->ways->out = (void *)start;
	pos->ways->truth = 0;
	out_add_tolist(&pos->ways, NULL, 1);
	pos->ways = pos->ways->begin;
	find->index_end = t_hash(find->n_end, room);
	find->lenght = 1;
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

void		ft_reset(t_stack *find, t_pos **pos)
{
	find->result = 0;
	find->espoir = 1;
	pos_init(pos, 0);
	(*pos)->ways->out = (void *)find->index_start;
	(*pos)->ways->truth = 0;
	out_add_tolist(&(*pos)->ways, NULL, 1);
	(*pos)->ways = (*pos)->ways->begin;
}

int			ft_edmonds(t_salle *room, t_stack *find, t_pos *pos, t_pos *path)
{
	t_struct	*way;
	int			max;
	int			t_instruct;

	find->espoir = 1; 
	find->lenght = 0;
	t_instruct = 0;
	max = fonc(find, room);
	if (!(way = (t_struct *)malloc(sizeof(t_struct) * (max + 1))))
		return (0);
	inti(way, find, max);
	ft_pathfirst(room, find, pos, path);
	find->result = 0;
	while (find->result == 0)
	{
		ft_clear(room, 0, pos);
		ft_clear(room, 1, path);
		ft_reset(find, &pos);
		while (t_instruct < 200)
		{
			ft_bfs(room, find, pos, path);
			pos = pos->begin;
			t_instruct++;
		}
		//find->result = 1;
		//print_allpos(path->begin, room);
	}
	leaks_struct(way, max);
	//print_allpos(path->begin, room);
	ft_clear(room, 2, path);
	return (1);
}
