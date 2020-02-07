/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:00:43 by damboule          #+#    #+#             */
/*   Updated: 2020/02/05 12:19:38 by damboule         ###   ########.fr       */
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

void	cases_init(t_cases **list, int i)
{
	if (!((*list) = (t_cases *)malloc(sizeof(t_cases) * 1)))
		return ;
	if (i == 0)
		(*list)->begin = (*list);
	(*list)->index = 0;
	(*list)->next = NULL;
}

void	path_init(t_path **path, t_salle *room, t_stack *find)
{
	int		i;
	int		len;

	i = 0;
	len = len_out(room[find->index_end].liens, 1) + 1;
	if (!((*path) = (t_path *)malloc(sizeof(t_path) * (len + 1))))
		return ;
	ft_memset(*path, 0, (sizeof(t_path) * len));
	while (i < len)
	{
		cases_init(&(*path)[i].cases, 0);
		(*path)[i].ants = 0;
		(*path)[i].length = 0;
		i++;
	}
}

void	stack_room_init(t_stack **info, t_salle **rooms)
{
	if (!((*info) = (t_stack *)malloc(sizeof(t_stack))))
		return ;
	if (!((*rooms) = (t_salle *)malloc(sizeof(t_salle) * t_size)))
		return ;
	ft_memset(*rooms, 0, (sizeof(t_salle) * t_size));
	(*info)->counter_del = 0;
	(*info)->finish = 1;
	(*info)->index_end = 0;
	(*info)->index_start = 0;
	(*info)->bhandari[0] = 0;
	(*info)->bhandari[1] = 0;
	(*info)->lenght = 0;
	(*info)->operation = 0;
	(*info)->result = 0;
	(*info)->salle = 0;
	(*info)->n_end = NULL;
	(*info)->n_start = NULL;
	(*info)->fourmies = -1;
}

void	init_algo(t_salle **room, t_stack **find, t_out **position, t_out **stack)
{
	(*find)->finish = 0;
	(*find)->bhandari[0] = 0;
	out_init(position, 0);
	out_init(stack, 0);
	(*position)->index = (*find)->index_start;
	(*room)[(*find)->index_start].free = 1;
	(*room)[(*find)->index_start].salle_prev[0] = (*find)->index_start;
}
