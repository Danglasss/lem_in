/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 08:48:54 by damboule          #+#    #+#             */
/*   Updated: 2020/02/02 19:51:19 by damboule         ###   ########.fr       */
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

void	clean_rep(t_salle *room, t_stack *find)
{
	t_out *link;

	link = room[find->index_end].liens->begin;
	room[find->index_end].ant_numb = 0;
	room[find->index_end].nb_salle = 0;
	while (link)
	{
		link->ant_numb = 0;
		link->nb_salle = 0;
		if (link->next == NULL)
			break ;
		link = link->next;
	}
	link = link->begin;
}

int		get_diff(unsigned long v_goals, t_salle *room, unsigned long end)
{
	room[end].liens = room[end].liens->begin;
	if (v_goals > (room[end].ant_numb + room[end].nb_salle))
		return (v_goals);
	while (room[end].liens->salle_prev != 0)
	{
		if ((room[end].liens->ant_numb + room[end].liens->nb_salle) >
								(room[end].ant_numb + room[end].nb_salle))
		{
			return (room[end].liens->ant_numb + room[end].liens->nb_salle);
		}
		room[end].liens = room[end].liens->next;
	}
	room[end].liens = room[end].liens->begin;
	return (v_goals + 1);
}

void	printrp(t_salle *room, t_stack *find)
{
	ft_printf("nombre de salle == %d !! nombre de fourmie == %d !! ligne == %d\n",
	room[find->index_end].nb_salle, room[find->index_end].ant_numb, room[find->index_end].nb_salle + room[find->index_end].ant_numb);
	room[find->index_end].liens = room[find->index_end].liens->begin;
	while (1)
	{
		if (room[find->index_end].liens->nb_salle != 0)
			ft_printf("nombre de salle == %d !! nombre de fourmie == %d !! ligne == %d\n",
		room[find->index_end].liens->nb_salle, room[find->index_end].liens->ant_numb, room[find->index_end].liens->nb_salle + room[find->index_end].liens->ant_numb);		
		if (room[find->index_end].liens->next == NULL)
			break ;
		room[find->index_end].liens = room[find->index_end].liens->next;
	}
	room[find->index_end].liens = room[find->index_end].liens->begin;
}

int		repart_eval(t_salle *room, t_stack *find, t_out *link, unsigned long ants)
{
	int		diff;
	
	printpath(room, find);
	diff = link->nb_salle;
	while (ants)
	{
		diff = get_diff(diff, room, find->index_end);
		if (diff > (room[find->index_end].ant_numb + room[find->index_end].nb_salle)
					&& ants)
		{
			ants--;
			room[find->index_end].ant_numb += 1;
		}
		while (link->salle_prev != 0)
		{	
			if (diff > (link->ant_numb + link->nb_salle)
					&& ants)
			{
				link->ant_numb += 1;
				ants--;
			}
			link = link->next;
		}
		link = link->begin;
	}
	diff = room[find->index_end].ant_numb + room[find->index_end].nb_salle;
	//printrp(room, find);
	clean_rep(room, find);
	return (diff);
}

void		best_shot_implement(t_salle *room, t_stack *find, t_path *best_shot)
{
	int len = len_out(room[find->index_end].liens, 1);
	int ind = 0;
	ft_clean_end(room, find);
	ft_clean(room, index);
	int i = 0;
	room[find->index_end].liens = room[find->index_end].liens->begin;
	while (ind < len)
	{
		//ft_printf("\n________________\n");
		best_shot[ind].cases = best_shot[ind].cases->begin;
		while (1)
		{
			if (best_shot[ind].cases->index != 0 && best_shot[ind].cases->next != NULL)
			{
				//ft_printf("%s--e\n", room[best_shot[ind].cases->index].salle);
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

void		bhandari(t_salle *room, t_stack *find, t_out *index, t_path	*best_shot)
{
	t_path	*current;

	path_init(&current, room, find);
	while (find->bhandari[0] < 1 && find->finish != 0)
	{
		algo(room, find, index, current);
		current->lines = repart_eval(room, find,
					room[find->index_end].liens->begin, find->fourmies);
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
	best_shot_implement(room, find, best_shot);
	return ;
}
