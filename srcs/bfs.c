/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:36:38 by nabboufe          #+#    #+#             */
/*   Updated: 2019/10/18 18:17:34 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	ft_copy(t_pos *pos, t_stack *find, t_pos *path)
{
	pos->finish = 1;
	find->result = 1;
	if (path->ways->begin->out == NULL)
	{
		cpy_length(&path->ways, pos->ways->begin, ULONG_MAX);
		path->salle = len_out(path->ways, 1);
		path->id = pos->id;
		path->colle = pos->colle;
	}
	else
	{
		pos_add_tolist(&path, NULL, 1);
		cpy_length(&path->ways, pos->ways->begin, ULONG_MAX);
		path->salle = len_out(path->ways, 1);
		path->id = pos->id;
		path->colle = pos->colle;
	}
}

void	ft_add_room(t_salle *room, t_pos *pos, t_stack *find,
		unsigned long t_index)
{
	if (room[(unsigned long)room[t_index].liens->out].path == 0)
		room[(unsigned long)room[t_index].liens->out].path = 1;
	if (pos->ways->out == NULL)
	{
		pos->ways->out = (void *)room[t_index].liens->out;
		pos->ways->truth = find->lenght;
	}
	else
	{
		out_add_tolist(&pos->ways, NULL, 1);
		pos->ways->truth = find->lenght;
		pos->ways->out = (void *)room[t_index].liens->out;
	}
	if (room[(unsigned long)room[t_index].liens->out].collision == NULL)
		room[(unsigned long)room[t_index].liens->out].collision->touch = pos->id;
	else
	{
		out_add_tolist(&room[(unsigned long)room[t_index].liens->out].collision, NULL, 1);
		room[(unsigned long)room[t_index].liens->out].collision->touch = pos->id;
	}
	if (room[t_index].liens->begin->next == NULL)
		pos->finish = -1;
}

int		ft_verif_ways(t_salle *room, t_stack *find, unsigned long t_index,
		long long prev_index)
{
	if (room[(unsigned long)room[t_index].liens->out].salle == NULL)
		return (0);
	if ((unsigned long)room[t_index].liens->out == find->index_start)
		return (0);
	if ((room[(unsigned long)room[t_index].liens->out].path == 0 || 
				find->index_end == (unsigned long)room[t_index].liens->out) && 
			(prev_index == -1 ||
			((unsigned int)prev_index !=
			(unsigned long)room[t_index].liens->out)))
		return (1);
	return (0);
}

int		ft_check_path(t_pos *path, long long index)
{
	path = path->begin;
	while (path != NULL)
	{
		path->ways = path->ways->begin;
		while (path->ways != NULL)
		{
			if ((long long)path->ways->out == index)
				return (1);
			if (path->ways->next == NULL)
				break;
			path->ways = path->ways->next;
		}
		if (path->next == NULL)
			break;
		path = path->next;
	}
	return (0);
}

int		ft_tina(t_salle *room, t_pos *path, long long *t_index)
{
	long long index;

	if (t_index[0] == - 1)
		return (0);
	room[(unsigned long)t_index[0]].liens = room[(unsigned long)t_index[0]].liens->begin;
	while (room[(unsigned long)t_index[0]].liens != NULL)
	{
		index = (unsigned long)room[(unsigned long)t_index[0]].liens->out;
		if (index != t_index[1] && (room[index].path == 0 || ft_check_path(path, index)))
			return (0);
		if (room[(unsigned long)t_index[0]].liens->next == NULL)
			break ;
		room[(unsigned long)t_index[0]].liens = room[(unsigned long)t_index[0]].liens->next;
	}
	return (1);
}

int		ft_verif_elem(t_salle *room, t_stack *find, long long *t_index, t_pos *path)
{
	if (room[(unsigned long)room[t_index[1]].liens->out].salle == NULL)
		return (0);
	if ((room[(unsigned long)room[t_index[1]].liens->out].path == 0 ||
				find->index_end == (unsigned long)room[t_index[1]].liens->out) &&
			(t_index[0] == -1 ||
			((unsigned int)t_index[0] !=
			(unsigned long)room[t_index[1]].liens->out)))
		return (1);
	(void)path;
	/*if (find->espoir == 1 &&
	room[(unsigned long)room[t_index[1]].liens->out].path == 1 && ft_check_path(path, t_index[1]) &&
	ft_tina(room, path, t_index))
		return (1);*/
	return (0);
}


int		dp(t_salle *room, long long *t_index, t_pos *pos)
{
	t_out *temp;

	temp = pos->ways->begin; 
	while (temp != NULL)  
	{
		if ((unsigned long)temp->out == (unsigned long)room[t_index[1]].liens->out)
			return (0);
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	return (1);
}

void	ft_main_bfs(t_salle *room, t_stack *find, t_pos *pos, t_pos *path)
{
	t_out				*tmp;
	int					count;
	long long			t_index[2];
	unsigned long		len_path;

	tmp = pos->ways->begin;
	ft_bzero(t_index, 2);
	ft_index(pos, &t_index[0], &t_index[1], &count);
	if (room[t_index[1]].liens != NULL && room[t_index[1]].liens->out != NULL)
		len_path = len_out(room[t_index[1]].liens, 1);
	else
		return ;
	while (pos->finish == 0 && len_path--)
	{
		if (count > 0 && ft_verif_ways(room, find, t_index[1], t_index[0])
				&& ft_add_way(&pos, pos->colle))
			cpy_length(&pos->ways, tmp, find->lenght - 1);
		if (ft_verif_elem(room, find, t_index, path) && ++count && dp(room, t_index, pos))
			ft_add_room(room, pos, find, t_index[1]);
		if (find->index_end == (unsigned long)room[t_index[1]].liens->out /*&& occur(pos->colle, path, pos)*/)
			ft_copy(pos, find, path);
		if (room[t_index[1]].liens->next != NULL && (unsigned long)room[t_index[1]].liens->next != find->index_start)
			room[t_index[1]].liens = room[t_index[1]].liens->next;
	}
	room[t_index[1]].liens = room[t_index[1]].liens->begin;
}
