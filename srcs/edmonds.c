/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 08:48:54 by damboule          #+#    #+#             */
/*   Updated: 2020/02/07 17:49:09 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	findpath(t_salle *room, t_stack *find, unsigned long end, t_path *current)
{
	int index;

	index = 0;
	//ft_printf("\n____________________________________\n");
	path(room, find, room[end].salle_prev[0], current[index].cases->begin);
	while (room[end].liens->salle_prev != 0)
	{
		index++;
		//ft_printf("\n\n");
		path(room, find, room[end].liens->salle_prev, current[index].cases->begin);
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

void		best_shot_implement(t_salle *room, t_stack *find, t_path *best_shot, int len)
{
	int ind;
	int i;

	i = 0;
	ind = 0;
	ft_clean_end(room, find);
	//ft_clean(room, index);
	room[find->index_end].liens = room[find->index_end].liens->begin;
	while (ind < len)
	{
		best_shot[ind].cases = best_shot[ind].cases->begin;
		while (1)
		{
			if (best_shot[ind].cases->index != 0 && best_shot[ind].cases->next != NULL)
			{
				if (i >= 1 && find->index_end == best_shot[ind].cases->index)
				{
					room[find->index_end].liens->salle_prev = best_shot[ind].cases->next->index;
					room[find->index_end].liens = room[find->index_end].liens->next;
				}
				else
					room[best_shot[ind].cases->index].salle_prev[0] = best_shot[ind].cases->next->index;
			}
			if (best_shot[ind].cases->next == NULL)
				break ;
			best_shot[ind].cases = best_shot[ind].cases->next;
		}
		i++;
		best_shot[ind].cases = best_shot[ind].cases->begin;
		ind++;
	}
	room[find->index_end].liens = room[find->index_end].liens->begin;
}

void	p(t_salle *room, t_stack *find, t_path *current)
{
	int nb_salle;
	int len;
	int index;

	len = len_out(room[find->index_end].liens, 1);
	index = 0;
	nb_salle = 0;
	while (index < len)
	{
		current[index].cases = current[index].cases->begin;
		while (1)
		{
			if (current[index].cases->index != 0)
				nb_salle++;
			if (current[index].cases->next == NULL)
				break ;
			current[index].cases = current[index].cases->next;
		}
		current[index].cases = current[index].cases->begin;
	//	ft_printf("line == %d !! path %d !! nb_salle %d\n", current[index].lines, index, nb_salle);
		nb_salle = 0;
		index++;
	}
}

void		bhandari(t_salle *room, t_stack *find, t_out *index, t_path	*best_shot)
{
	t_path	*current;

	path_init(&current, room, find);
	while (find->bhandari[0] < 1 && find->finish != 0)
	{
		algo(room, find, index, current);
		if (find->bhandari[0] != -1)
			current->lines = repart_eval(room, find,
					room[find->index_end].liens->begin, current);
		//ft_printf("lines == %d !! best == %d\n", current->lines, best_shot->lines);
		if (find->bhandari[0] == -1 && find->finish != 0)
		{
			//ft_printf("\n_____________________________\n");
			if (current->lines < best_shot->lines || best_shot->lines == 0)
				path_cpy(&best_shot, current, len_out(room[find->index_end].liens, 1));
			//ft_printf("lines == %d !! best == %d\n", current->lines, best_shot->lines);			
			clean_current(&current, len_out(room[find->index_end].liens, 1));
			ft_clean_end(room, find);
			ft_clean(room, index);
		}
	}
	if (current->lines < best_shot->lines || best_shot->lines == 0)
		return ;
	best_shot_implement(room, find, best_shot, len_out(room[find->index_end].liens, 1));
	leaks_path(current, len_out(room[find->index_end].liens, 1));
}
