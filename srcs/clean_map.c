/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 09:56:34 by damboule          #+#    #+#             */
/*   Updated: 2020/01/31 10:08:00 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		ft_cleaner(t_salle *room, t_stack *find, unsigned long salle, unsigned long del)
{
	unsigned long	tmp;
	int				len;
	
	while (1)
	{
		tmp = salle;
		salle = room[salle].salle_prev[1];	
		len = len_out(room[salle].liens, 1) - 1;
		if (len == 2)
		{
			room[salle].liens = room[salle].liens->begin;
			while ((unsigned long)room[salle].liens->out != tmp)
				room[salle].liens = room[salle].liens->next;
			room[salle].liens->out = NULL;
		}
		else if (len > 2)
		{
			room[salle].liens = room[salle].liens->begin;
			while ((unsigned long)room[salle].liens->out != tmp)
				room[salle].liens = room[salle].liens->next;
			room[salle].liens->out = NULL;
			break ;
		}
	}
	return (0);
}

int		ft_graph(t_salle *room, t_stack *find, t_out *position, t_out **stack)
{
	t_out	*liens;
	int		len;

	liens = room[position->index].liens;
	len = len_out(liens, 1) - 1;
    if (len == 1)
		return (ft_cleaner(room, find, position->index, (unsigned long)liens->out));
	while (liens)
	{
		if (room[(unsigned long)liens->out].free == 1 &&
							(unsigned long)liens->out != find->index_end)
		{
			liens = liens->next;
			continue ;
		}
		room[(unsigned long)liens->out].free = 1;
		room[(unsigned long)liens->out].salle_prev[1] = position->index;
		if (liens->next == NULL)
			break ;
		next(&liens, stack);
	}
	return (0);
}

void	clean_map(t_salle *room, t_stack *find, t_out *index)
{
	t_out	*stack;
	t_out	*position;
	int		clean;
	int		len;
	
	clean = 1;
	out_init(&position, 0);
	out_init(&stack, 0);
	position->index = find->index_start;
	while (clean)
	{
		len = len_out(position, 1) - 1;
		while (position)
		{
			if (position->index == 0)
				len--;
			if (position->index != 0 && position->index != find->index_end)
				ft_graph(room, find, position, &stack);
			if (position->next == NULL)
				break ;
			if (len == 0)
				clean = 0;
			position = position->next;
		}
		cpy_length(&position, stack, &stack);
		position = position->begin;
		stack = stack->begin;
	}
	clear(room, find, index);
	ft_reset(room, index);
}