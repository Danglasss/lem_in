/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:17:22 by damboule          #+#    #+#             */
/*   Updated: 2019/12/24 11:34:59 by danglass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void    set_room(t_stack *info, t_salle *room, t_pos *path)
{
    room[(unsigned long)path->ways->next->out].n_lem = 
        room[(unsigned long)path->ways->out].n_lem;
    if ((unsigned long)path->ways->next->out != info->index_end)
    {
        room[(unsigned long)path->ways->next->out].path = 1;
        path->ways->next->truth = 1;
    }
    else
        info->espoir += 1;
    room[(unsigned long)path->ways->out].path = 0;
    room[(unsigned long)path->ways->out].n_lem = 0;
    path->ways->truth = 0;
}

void    move_f(t_stack *info, t_salle *room, t_pos *path, int *n_lem)
{
	while (path->ways->prev != NULL)
    {
        if (path->ways->next != NULL && room[(unsigned long)path->ways->out].path == 1
                && room[(unsigned long)path->ways->next->out].path == 0
                && path->ways->truth == 1)
        {
            set_room(info, room, path);
            ft_printf("L%d-%s ", room[(unsigned long)path->ways->next->out].n_lem,
                room[(unsigned long)path->ways->next->out].salle);
        }
        path->ways = path->ways->prev;
    }
    if ((unsigned long)path->ways->out == info->index_start
            && room[(unsigned long)path->ways->next->out].path == 0
            && path->fourmies > 0 && *n_lem <= info->fourmies)
    {
        room[(unsigned long)path->ways->next->out].path = 1;
        path->ways->next->truth = 1;
        room[(unsigned long)path->ways->next->out].n_lem = *n_lem;
        *n_lem += 1;
        ft_printf("L%d-%s ", room[(unsigned long)path->ways->next->out].n_lem,
                room[(unsigned long)path->ways->next->out].salle);
        path->fourmies -= 1;
    }
}

void    do_ways(t_stack *info, t_salle *room, t_pos *path)
{
    int     n_lem;
    int     count = 0;

    n_lem = 1;
    while (info->fourmies >= info->espoir)
    {
        path = path->begin;
        while (path != NULL)
        {
            out_end(&path->ways);
            move_f(info, room, path, &n_lem);
            if (path->next == NULL)
                break ;
            path = path->next;
        }
        ft_printf("\n");
        count++;
    }
}

void		ft_put(t_salle *room, t_pos *pos)
{
	pos = pos->begin;
	while (pos != NULL)
	{
		pos->ways = pos->ways->begin;
		while (pos->ways != NULL)
		{
			room[(unsigned long)pos->ways->out].path = 1;
			if (pos->ways->next == NULL)
				break ;
			pos->ways = pos->ways->next;
		}
		if (pos->next == NULL)
			break ;
		pos = pos->next;
	}
}

void    t_end(t_stack *info, t_salle *room, t_pos *path)
{
    f_equal(path->begin, info->fourmies - f_repartition(path->begin));
    do_ways(info, room, path->begin);
}
