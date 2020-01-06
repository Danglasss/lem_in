/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:36:38 by nabboufe          #+#    #+#             */
/*   Updated: 2020/01/03 16:38:09 by danglass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	next(t_out **liens, t_out **stack)
{
	(*liens) = (*liens)->next;
	if ((*stack)->next == NULL)
		out_add_tolist(stack, NULL, 1);
	else
		(*stack) = (*stack)->next;
}

int		suplink(t_out *link, t_stack *find)
{
	link = link->begin;
	while (link)
	{
		if (link->open == 1 && find->index_start != (unsigned long)link->out)
			return (1);
		if (link->next  == NULL)
			break ;
		link = link->next;
	}
	link = link->begin;
	return (0);
} 

int		toplink(t_out *link, t_stack *find, t_salle *room, unsigned long index)
{
	link = link->begin;
	while (link)
	{
		if ((unsigned long)link->out == room[index].salle_prev[0] || (unsigned long)link->out == 0)
		{
			if (link->next == NULL)
				break ;
			link = link->next;
			continue ;
		}
		if ((link->open == 0 || link->open == 1) && find->index_start != (unsigned long)link->out)
			return (1);
		if (link->next  == NULL)
			break ;
		link = link->next;
	}
	link = link->begin;
	return (0);
} 

int		ft_open(t_salle *room, t_out *liens, t_stack *find, unsigned long index)
{
	if (room[(unsigned long)liens->out].free == 1 &&
		(unsigned long)liens->out != find->index_end)
		return (1);
	if (liens->open == -1)
		return (1);
	if (liens->open == 0 && suplink(liens, find))
		return (1);
	if (liens->open == 3 && toplink(liens, find, room, index))
		return (1);
	if (liens->del == 1)
		return (1);
	return (0);
}

void	delete_link(t_out **liens, t_salle *room, unsigned long salle)
{
	int len;
	
	(*liens)->del = 1;
	room[(unsigned long)(*liens)->out].liens = room[(unsigned long)(*liens)->out].liens->begin;
	len = len_out(room[(unsigned long)(*liens)->out].liens, 1) - 1;
	while ((unsigned long)room[(unsigned long)(*liens)->out].liens->out != salle)
	{
		room[(unsigned long)(*liens)->out].liens
		= room[(unsigned long)(*liens)->out].liens->next;
		len--;
	}
	room[(unsigned long)(*liens)->out].liens->del = 1;
	room[(unsigned long)(*liens)->out].liens = room[(unsigned long)(*liens)->out].liens->begin;
}

int		ft_delcheck(unsigned long path, t_salle *room)
{
	while (room[path].liens)
	{
		if (room[path].liens->del == 1)
		{
			room[path].liens = room[path].liens->begin;
			return (0);
		}
		if (room[path].liens->next == NULL)
			break ;
		room[path].liens = room[path].liens->next;
	}
	room[path].liens = room[path].liens->begin;
	return (1);
}

int		ft_check(unsigned long path, unsigned long salle, t_stack *find, t_salle *room)
{	
	while (path != find->index_start)
	{
		if (path == salle && ft_delcheck(path, room)) // also check if lien del
			return (1);
		path = room[path].salle_prev[0];
	}
	return (0);
}

int		verify_colision(t_salle *room, unsigned long salle, t_stack *find, t_out **stack)
{
	unsigned long index;
	unsigned long end;
	
	index = salle;
	end = find->index_end;
	while (index != find->index_start)
	{
		if (ft_check(room[end].salle_prev[0], index, find, room))
			return (0);
		while (room[end].liens->salle_prev != 0)
		{
			if (ft_check(room[end].liens->salle_prev, index, find, room))
				return (0);
			if (room[end].liens->next == NULL)
				break ;
			room[end].liens = room[end].liens->next;
		}
		room[end].liens = room[end].liens->begin;
		index = room[index].salle_prev[0];
	}
	return (1);
}

void	blockchain(t_salle *room, unsigned long salle_prev, t_stack *find, t_out **stack)
{
	room[(*stack)->index].free = 1;
	if (find->index_end != (*stack)->index || room[(*stack)->index].salle_prev[0] == 0)
		room[(*stack)->index].salle_prev[0] = salle_prev;
	else if (find->index_end == (*stack)->index && verify_colision(room, salle_prev, find, stack))
	{
		while (room[(*stack)->index].liens->salle_prev != 0)
			room[(*stack)->index].liens = room[(*stack)->index].liens->next;
		room[(*stack)->index].liens->salle_prev = salle_prev;
		room[(*stack)->index].liens = room[(*stack)->index].liens->begin;
	}
}

int		bfs(t_salle *room, t_stack *find, t_out *position, t_out **stack)
{
	int		bhandari_state;
	t_out	*liens;

	liens = room[position->index].liens;
	bhandari_state = 0;
	print_lien(liens, room);
	while (liens)
	{
		if (ft_open(room, liens, find, position->index))
		{
			liens = liens->next;
			continue ;
		}
		(*stack)->index = (unsigned long)liens->out;
		blockchain(room, position->index, find, stack);
		if (liens->open == 1)
		{
			bhandari_state = -1;
			delete_link(&liens, room, position->index);
		}
		next(&liens, stack);
	}
	return (bhandari_state);
}

int		finish(t_salle *room, t_stack *find, t_out *index)
{
	int				len;
	int				lenght;

	if (room[find->index_end].salle_prev[0] != 0)
		len = 1;
	lenght = len_out(room[find->index_end].liens, 1) - 1;
	while (room[find->index_end].liens)
	{
		if (room[find->index_end].liens->open == -1)
			len++;
		else if (room[find->index_end].liens->salle_prev != 0)
			len++;
		if (lenght == len)
			return (1);
		if (room[find->index_end].liens->next == NULL)
			break ;
		room[find->index_end].liens = room[find->index_end].liens->next;
	}
	room[find->index_end].liens = room[find->index_end].liens->begin;
	return (0);
}

int		algo(t_salle *room, t_stack *find, t_out *index)
{
	t_out	*position;
	t_out	*stack;
	int		bhandari_state;

	out_init(&position, 0);
	out_init(&stack, 0);
	position->index = find->index_start;
	bhandari_state = 0;
	// a definir dans initialisation
	room[find->index_start].free = 1;
	room[find->index_start].salle_prev[0] = find->index_start;
	//
	while (room[find->index_end].free == 0)
	{
		//ft_printf("\nCommence \n");
		while (position)
		{
			//if (room[position->index].salle != NULL)
			ft_printf("\n\nSALLE : %s\n", room[position->index].salle);
			if (position->index != 0)
				bhandari_state += bfs(room, find, position, &stack);
			//print(stack->begin, room);			
			if (position->next == NULL)
				break ;
			position = position->next;
		}
		ft_printf("\n___________\n");
		cpy_length(&position, stack);
		position = position->begin;
		stack = stack->begin;
	}
	findpath(room, find, find->index_end);
	clear(room, find, index);
	if (bhandari_state != -1)
		bhandari_state += finish(room, find, index);
	return (bhandari_state);
}
