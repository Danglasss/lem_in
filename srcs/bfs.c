/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:36:38 by dygouin          #+#    #+#             */
/*   Updated: 2020/01/30 15:04:38 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	delete_link(t_out **liens, t_salle *room, unsigned long salle)
{
	int len;

	(*liens)->del[1] = 1;
	room[(unsigned long)(*liens)->out].liens = room[(unsigned long)(*liens)->out].liens->begin;
	len = len_out(room[(unsigned long)(*liens)->out].liens, 1) - 1;
	while ((unsigned long)room[(unsigned long)(*liens)->out].liens->out != salle)
	{
		room[(unsigned long)(*liens)->out].liens
		= room[(unsigned long)(*liens)->out].liens->next;
		len--;
	}
	room[(unsigned long)(*liens)->out].liens->del[1] = 1;
	room[(unsigned long)(*liens)->out].liens = room[(unsigned long)(*liens)->out].liens->begin;
}

void	blockchain(t_salle *room, unsigned long salle_prev, t_stack *find, unsigned long stack)
{
	if (find->index_end != stack || room[stack].salle_prev[0] == 0)
	{
		room[stack].salle_prev[1] = salle_prev;
		if (room[stack].ascend == 0)
			room[stack].lenght = room[salle_prev].lenght + 1;
		else
			room[stack].lenght = room[salle_prev].lenght - 1;
		if (find->index_end == stack)
		{
			transfert_true(room, find, salle_prev);
			room[find->index_end].salle_prev[0] = room[find->index_end].salle_prev[1];
			find->finish = 1;
		}
		room[stack].free = 1;
	}
	else if (find->index_end == stack)
	{
		while (room[stack].liens->salle_prev != 0)
			room[stack].liens = room[stack].liens->next;
		room[stack].liens->salle_prev = salle_prev;
		room[stack].liens = room[stack].liens->begin;
		transfert_true(room, find, salle_prev);
		find->finish = 1;
		room[stack].free = 1;
	}
}	

int		stop_up(t_out *link, t_stack *find, t_salle *room, unsigned long index)
{
	link = link->begin;
	while (link)
	{
		if (link->open == 0 && find->index_start != (unsigned long)link->out)
			return (1);
		if (link->open == 3 
				&& room[index].lenght < room[(unsigned long)link->out].lenght)
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
	if ((unsigned long)liens->out == EMPTY || liens->del[0] == DEL || liens->open == CLOSE)
		return (1);
	if (liens->open == 3 && toplink(liens, find, room, index))
		return (1);
	if (liens->open == 1 && room[index].ascend == 1
			&& stop_up(liens, find, room, index))
		return (1);
	if (liens->open == 1)
		return (0);
	if (room[(unsigned long)liens->out].free == VISITED && room[index].ascend == 1 &&
					room[index].lenght + 1 < room[(unsigned long)liens->out].lenght && liens->open == 3)
		return (0);
	if (room[(unsigned long)liens->out].free == VISITED &&
					(unsigned long)liens->out != find->index_end)
		return (1);
	if ((unsigned long)liens->out == find->index_end && room[find->index_end].salle_prev[0] != 0 &&
				verify_colision(room, index, find) == 0)
		return (1);
	return (0);
}

int		bfs(t_salle *room, t_stack *find, unsigned long position, t_out **stack)
{
	t_out	*liens;

	liens = room[position].liens->begin;
	//ft_printf("ascend == %d\n", room[position].ascend);
	//print_lien(liens, room);
	while (liens)
	{
		if (ft_open(room, liens, find, position))
		{
			liens = liens->next;
			continue ;
		}
		if (liens->open == 1)
		{
			delete_link(&liens, room, position);
			room[(unsigned long)liens->out].ascend = 1;
			blockchain(room, position, find, (unsigned long)liens->out);		
			bfs(room, find, (unsigned long)liens->out, stack);
			liens = liens->next;
			continue ;
		}
		(*stack)->index = (unsigned long)liens->out;
		blockchain(room, position, find, (unsigned long)liens->out);
		next(&liens, stack);
	}
	return (0);
}

void		algo(t_salle *room, t_stack *find, t_out *index)
{
	t_out	*position;
	t_out	*stack;
	int 	len;

	out_init(&position, 0);
	out_init(&stack, 0);
	position->index = find->index_start;
	room[find->index_start].free = 1;
	room[find->index_start].salle_prev[0] = find->index_start;
	while (room[find->index_end].free == EMPTY)
	{
		//ft_printf("\nCommence \n");
		len = len_out(position, 1) - 1;
		while (position)
		{
			//ft_printf("\n\nSALLE : %s || %d\n", room[position->index].salle, position->index);
			if (position->index == EMPTY)
				len--;
			if (position->index != EMPTY)
				bfs(room, find, position->index, &stack);
			//print(stack->begin, room);			
			if (position->next == NULL)
				break ;
			if (len == 0)
				room[find->index_end].free = 1;
			position = position->next;
		}
		//ft_printf("\n___________\n");
		cpy_length(&position, stack);
		position = position->begin;
		stack = stack->begin;
	}
	main_reset(room, find, index);
}
