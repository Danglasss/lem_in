/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 08:48:54 by damboule          #+#    #+#             */
/*   Updated: 2020/02/13 18:17:42 by danglass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	findpath(t_salle *room, t_stack *find,
unsigned long end, t_path *current)
{
	int index;

	index = 0;
	path(room, find, room[end].salle_prev[0], current[index].cases->begin);
	while (room[end].liens->salle_prev != 0)
	{
		index++;
		path(room, find, room[end].liens->salle_prev,
		current[index].cases->begin);
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

void	ft_drawpath(t_salle *room, t_cases *path, t_stack *find, int begin)
{
	path = path->begin;
	while (path != NULL)
	{
		if (path->index != 0 && path->next != NULL)
		{
			if (find->index_end == path->index && begin >= 1)
				room[find->index_end].liens->salle_prev = path->next->index;
			else
				room[path->index].salle_prev[0] = path->next->index;
		}
		if (path->next == NULL)
			break ;
		path = path->next;
	}
}

void	best_shot_implement(t_salle *room, t_stack *find,
t_path *best_shot, int len)
{
	int index;
	int begin;

	begin = 0;
	index = 0;
	ft_clean_end(room, find);
	room[find->index_end].liens = room[find->index_end].liens->begin;
	while (index < len)
	{
		ft_drawpath(room, best_shot[index].cases->begin, find, begin);
		if (begin >= 1)
			room[find->index_end].liens = room[find->index_end].liens->next;
		best_shot[index].cases = best_shot[index].cases->begin;
		begin++;
		index++;
	}
	room[find->index_end].liens = room[find->index_end].liens->begin;
}

void	bhandari(t_salle *room, t_stack *find,
							t_out *index, t_path *best_shot)
{
	t_path	*current;

	path_init(&current, room, find);
	while (find->bhandari[0] < 1 && find->finish != 0)
	{
		algo(room, find, index, current);
		if (find->bhandari[0] != -1)
			current->lines = repart_eval(room, find,
					room[find->index_end].liens->begin, current);
		if (find->bhandari[0] == -1 && find->finish != 0)
		{
			if (current->lines < best_shot->lines || best_shot->lines == 0)
				path_cpy(&best_shot, current,
				len_out(room[find->index_end].liens, 1));
			leaks_path(current, len_out(room[find->index_end].liens, 1));
			path_init(&current, room, find);
			//clean_current(&current, len_out(room[find->index_end].liens, 1));
			ft_clean_end(room, find);
			ft_clean(room, index);
		}
	}
	if (current->lines < best_shot->lines || best_shot->lines == 0)
	{
		leaks_path(current, len_out(room[find->index_end].liens, 1));
		return ;
	}
	best_shot_implement(room, find, best_shot,
	len_out(room[find->index_end].liens, 1));
	leaks_path(current, len_out(room[find->index_end].liens, 1));
}
