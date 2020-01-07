/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:00:43 by damboule          #+#    #+#             */
/*   Updated: 2020/01/07 19:52:55 by danglass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	out_init(t_out **list, int i)
{
	if (!((*list) = (t_out *)malloc(sizeof(t_out))))
		return ;
	if (i == 0)
		(*list)->begin = (*list);
	(*list)->nb_salle = 0;
	(*list)->ant_numb = 0;
	(*list)->truth = 1;
	(*list)->del = 0;
	(*list)->salle_prev = 0;
	(*list)->index = 0;
	(*list)->open = 0;
	(*list)->out = NULL;
	(*list)->next = NULL;
	(*list)->prev = NULL;
}

void	pos_init(t_pos **list, int i)
{
	if (!((*list) = (t_pos *)malloc(sizeof(t_pos))))
		return ;
	if (i == 0)
		(*list)->begin = (*list);
	out_init(&(*list)->ways, 0);
	(*list)->next = NULL;
	(*list)->prev = NULL;
	(*list)->finish = 0;
	(*list)->colle = 0;
	(*list)->fourmies = 0;
	(*list)->instruction = 0;
	(*list)->salle = 0;
	(*list)->id = 0;
}

void	stack_room_init(t_stack **info, t_salle **rooms)
{
	if (!((*info) = (t_stack *)malloc(sizeof(t_stack))))
		return ;
	if (!((*rooms) = (t_salle *)malloc(sizeof(t_salle) * t_size)))
		return ;
	ft_memset(*rooms, 0, (sizeof(t_salle) * t_size));	
	(*info)->index_end = 0;
	(*info)->index_start = 0;
	(*info)->lenght = 0;
	(*info)->operation = 0;
	(*info)->result = 0;
	(*info)->salle = 0;
	(*info)->ways = 0;
	(*info)->n_end = NULL;
	(*info)->n_start = NULL;
	(*info)->fourmies = -1;
}

void	init_leak(t_out **reads, t_out **index, t_pos **path, t_pos **pos)
{
	leaks_out(*reads);
	leaks_out(*index);
	leaks_pos(*pos);
	leaks_pos(*path);
}

int		free_reset(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (1);
}
