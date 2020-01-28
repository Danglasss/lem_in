/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:36:38 by nabboufe          #+#    #+#             */
/*   Updated: 2020/01/28 16:41:52 by damboule         ###   ########.fr       */
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

void	blockchain(t_salle *room, unsigned long salle_prev, t_stack *find, t_out **stack)
{
	room[(*stack)->index].free = 1;
	if (find->index_end != (*stack)->index || room[(*stack)->index].salle_prev[0] == 0)
	{
		room[(*stack)->index].salle_prev[1] = salle_prev;
		if (find->index_end == (*stack)->index)
		{
			transfert_true(room, find, salle_prev);
			room[find->index_end].salle_prev[0] = room[find->index_end].salle_prev[1];
			find->finish = 1;
		}
	}
	else if (find->index_end == (*stack)->index && verify_colision(room, salle_prev, find, stack))
	{
		while (room[(*stack)->index].liens->salle_prev != 0)
			room[(*stack)->index].liens = room[(*stack)->index].liens->next;
		room[(*stack)->index].liens->salle_prev = salle_prev;
		room[(*stack)->index].liens = room[(*stack)->index].liens->begin;
		transfert_true(room, find, salle_prev);
		find->finish = 1;
	}
}	

int		stop_up(t_out *link, t_stack *find)
{
	link = link->begin;
	while (link)
	{
		if ((link->open == 3 || link->open == 5 || link->open == 0) && find->index_start != (unsigned long)link->out)
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
	if ((unsigned long)liens->out == 0)
		return (1);
	if (liens->del[0] == 1)
		return (1);
	if (liens->open == -1)
		return (1);
	/*if (liens->open == 1 
		&& lien_double(room, room[index].salle_prev[1], liens->begin) == 0
			&& stop_up(liens, find))
		return (1);*/
	if (liens->open == 1)
		return (0);
	if (room[(unsigned long)liens->out].free == 1 &&
		(unsigned long)liens->out != find->index_end)
		return (1);
	if (liens->open == 5 && toplink(liens, find, room, index))
		return (1);
	if (liens->open == 3 && toplink(liens, find, room, index))
		return (1);
	return (0);
}

int		bfs(t_salle *room, t_stack *find, unsigned long position, t_out **stack)
{
	t_out	*liens;

	liens = room[position].liens;
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
			(*stack)->index = (unsigned long)liens->out;
			blockchain(room, position, find, stack);		
			bfs(room, find, (unsigned long)liens->out, stack);
			liens = liens->next;
			continue ;
		}
		(*stack)->index = (unsigned long)liens->out;
		blockchain(room, position, find, stack);
		next(&liens, stack);
	}
	return (0);
}

int		algo(t_salle *room, t_stack *find, t_out *index)
{
	t_out	*position;
	t_out	*stack;
	int		bhandari_state;
	int 	len;

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
		len = len_out(position, 1) - 1;
		while (position)
		{
			//ft_printf("\n\nSALLE : %s || %d\n", room[position->index].salle, position->index);
			if (position->index == 0)
				len--;
			if (position->index != 0)
				bfs(room, find, position->index, &stack);
			//print(stack->begin, room);			
			if (position->next == NULL)
				break ;
			if (len == 0)
			{
				find->finish = 0;
				room[find->index_end].free = 1;
			}
			position = position->next;
		}
		//ft_printf("\n___________\n");
		cpy_length(&position, stack);
		position = position->begin;
		stack = stack->begin;
	}
	//ft_printf("\n_____Finish : %d\n", find->finish);
	if (find->finish != 0 && find->bhandari[0] != -1)
		findpath(room, find, find->index_end);
	//ft_printf("\n_____Finish__2____\n");
	//exit(1);
	clear(room, find, index);
	if (find->bhandari[0] != -1)
		find->bhandari[0] += finish(room, find, index);
	return (bhandari_state);
}
