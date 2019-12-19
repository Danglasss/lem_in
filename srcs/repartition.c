/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repartition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 10:16:23 by damboule          #+#    #+#             */
/*   Updated: 2019/10/18 16:54:17 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void		ft_begin(t_stack *find, t_pos *pos, t_salle *room)
{
	unsigned long		start;

	start = t_hash(find->n_start, room);
	find->ways = 0;
	find->result = 0;
	pos->ways->out = (void *)start;
	pos->ways->truth = 0;
	out_add_tolist(&pos->ways, NULL, 1);
	pos->ways = pos->ways->begin;
	find->index_end = t_hash(find->n_end, room);
	find->lenght = 1;
}

void	ft_set_reset(t_salle *room, t_stack *find, t_pos *pos, t_pos *path)
{
	int				count;
	
	ft_begin(find, pos, room);
	ft_bfs(room, find, pos, path);
	count = 0;
	pos = pos->begin;
	while (pos)
    {
		pos->colle = count;
		if (pos->next == NULL)
			break ;
		count++;
		pos = pos->next;
	}
}

int		occur(int colle, t_pos *path, t_pos *pos)
{
	path = path->begin;
	(void)pos;
	while (path)
	{
		if (path->colle == colle)
			return (1);
		if (path->next == NULL)
			break ;
		path = path->next;
	}
	return (1);
}