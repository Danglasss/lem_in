/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lead_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:24:42 by nabboufe          #+#    #+#             */
/*   Updated: 2019/09/12 08:26:57 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void		bfs_fourmies(t_pos *path, t_stack *info, int index, t_salle *room)
{
	nout_next(&path->ways, index);
	if ((unsigned long)path->ways->out == info->index_end)
		info->operation = 0;
	while (path != NULL && path->ways != NULL)
	{
		if ((unsigned long)path->ways->out == info->index_start)
		{
			if (info->espoir < info->fourmies /*&& path->fourmies > 0*/)
			{
				path->ways->truth = info->espoir;
				//path->fourmies -= 1;
			}
			else
			{
				path->ways->truth = -1;
			}
			info->espoir += 1;
		}
		if (path->ways->next != NULL && (unsigned long)path->ways->next->out == info->index_end)
			room[info->index_end].n_lem += 1;
		if (path->ways->truth == -1)
			break ;
		if (path->ways->next != NULL)
			path->ways->next->truth = path->ways->truth;
		if (path->ways->truth != -1 && (path->ways->prev == NULL || path->ways->truth != path->ways->prev->truth))
			ft_printf("L%d-%s ", path->ways->truth, room[(unsigned long)path->ways->out].salle);
		if (path->ways->prev != NULL)
			path->ways = path->ways->prev;
		else
			break ;
	}
}

void		affichage(t_stack *info, t_salle *room, t_pos *path)
{
	int		tmp;
	int		phase;

	phase = 1;
	tmp = info->fourmies;
	info->espoir = 1;
	info->operation = 1;
	path = path->begin;
	path->ways = path->ways->begin;
	print_allpos(path, room);
	exit(1);
	while (path != NULL)
	{
		path->ways->truth = info->espoir;
		ft_printf("L%d-%s ", path->ways->truth, room[(unsigned long)path->ways->out].salle);
		info->espoir += 1;
		if (path->next != NULL)
			path = path->next;
		else
			break ;
	}
	ft_printf("\n");
	while (room[info->index_end].n_lem < tmp)
	{

		bfs_fourmies(path, info, phase, room);
		path->ways = path->ways->begin;
		if (path->next != NULL)
			path = path->next;
		else
		{
			ft_printf("\n");
			path = path->begin;
			if (info->operation == 1)
				phase++;
		}
	}
}