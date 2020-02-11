/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:36:38 by dygouin          #+#    #+#             */
/*   Updated: 2020/02/11 13:49:44 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	block_end(t_salle *room, t_stack *find, unsigned long stack, unsigned long salle_prev)
{
	while (room[stack].liens->salle_prev != 0)
		room[stack].liens = room[stack].liens->next;
	room[stack].liens->salle_prev = salle_prev;
	room[stack].liens = room[stack].liens->begin;
	transfert_true(room, find, salle_prev);
	find->finish = 1;
	room[stack].free = 1;
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
			room[find->index_end].salle_prev[0] =
			room[find->index_end].salle_prev[1];
			find->finish = 1;
		}
		room[stack].free = 1;
	}
	else if (find->index_end == stack)
		block_end(room, find, stack, salle_prev);
}

int		ft_open(t_salle *room, t_out *liens, t_stack *find, unsigned long index)
{
	if ((unsigned long)liens->out == EMPTY || liens->del[0] == DEL || liens->open == CLOSE)
		return (1);
	if (liens->open == 3 && toplink(liens, find, room, index))
		return (1);
	if ((liens->open == 1 && room[index].ascend == 1 && stop_up(liens, find, room, index))
		|| (liens->open == 1 && room[(unsigned long)liens->out].free == VISITED
			&& same_path(room, find, index, (unsigned long)liens->out)))
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
	int		ret;

	liens = room[position].liens->begin;
	while (liens)
	{
		if ((ret = ft_open(room, liens, find, position)) || liens->open == 1)
		{
			if (liens->open == 1 && ret != 1)
			{	
				delete_link(&liens, room, position);
				blockchain(room, position, find, (unsigned long)liens->out);		
				bfs(room, find, (unsigned long)liens->out, stack);
			}
			liens = liens->next;
			continue ;
		}
		blockchain(room, position, find, (unsigned long)liens->out);
		next(&liens, stack);
	}
	return (0);
}

void		algo(t_salle *room, t_stack *find, t_out *index, t_path *current)
{
	t_out		*position;
	t_out		*stack;
	int 		len;

	init_algo(&room, &find, &position, &stack);
	while (room[find->index_end].free == EMPTY)
	{
		len = len_out(position, 1) - 1;
		while (position)
		{
			if (position->index == EMPTY)
				len--;
			if (position->index != EMPTY)
				bfs(room, find, position->index, &stack);
			if (position->next == NULL || find->bhandari[0] == -1)
				break ;
			if (len == 0)
				room[find->index_end].free = 1;
			position = position->next;
		}
		cpy_length(&position, stack, &stack);
	}
	main_reset(room, find, index, current);
	leaks_out(stack, 0);
	leaks_out(position, 0);
}
