/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 09:56:34 by damboule          #+#    #+#             */
/*   Updated: 2020/02/26 16:17:08 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_cleaner(t_salle *room, t_stack *find, unsigned long salle)
{
	unsigned long	tmp;
	int				len;

	while (salle != find->index_start)
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
}

void	ft_graph(t_salle *room, t_stack *find, t_out *position, t_out **stack)
{
	t_out	*liens;
	int		len;

	liens = room[position->index].liens;
	len = len_out(liens, 1) - 1;
	if (len == 1 && (unsigned long)room[position->index].liens->out !=
		find->index_end && position->index != find->index_start)
	{
		return (ft_cleaner(room, find, position->index));
	}
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
}

int		clean_map3(t_out *stack, t_out *position, t_salle *room, t_out *index)
{
	ft_reset(room, index);
	leaks_out(stack, 0);
	leaks_out(position, 0);
	return (0);
}

int		clean_map2(t_out **stack, t_out **position, t_stack *find)
{
	out_init(&(*position), 0);
	out_init(&(*stack), 0);
	(*position)->index = find->index_start;
	return (1);
}

int		clean_map(t_salle *room, t_stack *find, t_out *index)
{
	t_out	*stack;
	t_out	*position;
	int		clean;
	int		len;

	clean = clean_map2(&stack, &position, find);
	while (clean)
	{
		len = len_out(position, 1) - 1;
		while (position)
		{
			if (position->index != 0 && position->index != find->index_end)
				ft_graph(room, find, position, &stack);
			if (ft_break(&len, &clean, &position))
				break ;
			position = position->next;
		}
		cpy_length(&position, stack, &stack);
	}
	if (room[find->index_end].free == 0 && write(2, "ERROR\n", 6))
		return (clean_map3(stack, position, room, index));
	clear(room, index);
	clean_map3(stack, position, room, index);
	return (1);
}
