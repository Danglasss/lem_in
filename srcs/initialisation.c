/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:00:43 by damboule          #+#    #+#             */
/*   Updated: 2020/01/31 11:11:32 by damboule         ###   ########.fr       */
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
	(*list)->del[0] = 0;
	(*list)->del[1] = 0;
	(*list)->salle_prev = 0;
	(*list)->index = 0;
	(*list)->open = 0;
	(*list)->out = NULL;
	(*list)->next = NULL;
	(*list)->prev = NULL;
}

void	banned_init(t_banned **list, int i)
{
	if (!((*list) = (t_banned *)malloc(sizeof(t_banned))))
		return ;
	if (i == 0)
		(*list)->begin = (*list);
	(*list)->room1 = 0;
	(*list)->room2 = 0;
	(*list)->next = NULL;
	
}

void	shot_init(t_snapshot **list)
{
	if (!((*list) = (t_snapshot *)malloc(sizeof(t_snapshot))))
		return ;
	(*list)->lines = 0;
	banned_init(&(*list)->banned, 0);	
}

void	stack_room_init(t_stack **info, t_salle **rooms)
{
	if (!((*info) = (t_stack *)malloc(sizeof(t_stack))))
		return ;
	if (!((*rooms) = (t_salle *)malloc(sizeof(t_salle) * t_size)))
		return ;
	ft_memset(*rooms, 0, (sizeof(t_salle) * t_size));	
	(*info)->finish = 1;
	(*info)->index_end = 0;
	(*info)->index_start = 0;
	(*info)->bhandari[0] = 0;
	(*info)->bhandari[1] = 0;
	(*info)->lenght = 0;
	(*info)->operation = 0;
	(*info)->result = 0;
	(*info)->salle = 0;
	(*info)->ways = 0;
	(*info)->n_end = NULL;
	(*info)->n_start = NULL;
	(*info)->fourmies = -1;
}

int		free_reset(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (1);
}
