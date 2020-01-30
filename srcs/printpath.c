/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:58:39 by damboule          #+#    #+#             */
/*   Updated: 2020/01/30 14:36:16 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		p_salle(t_salle *room, t_stack *find, unsigned long end, unsigned long salle_prev)
{
	unsigned long	index;
	unsigned long	tmp;
	int				len;
	index = end;
	while (index != find->index_start)
	{
		len++;
		if (index == find->index_end)
		{
			index = salle_prev;
			continue ;
		}
		index = room[index].salle_prev[0];
	}
	return (len);
}
void	printpath(t_salle *room, t_stack *find)
{
	unsigned long	end;
	int				len;
	int				index;
	end = find->index_end;
	index = 1;
	ft_printf("\n-------\n");
	len = p_salle(room, find, find->index_end, room[end].salle_prev[0]);
	ft_printf("path == %d\nsalle == %d\n\n", index, len);
	while (room[end].liens->salle_prev != 0)
	{
		index++;
		len = p_salle(room, find, find->index_end, room[end].liens->salle_prev);
		ft_printf("path == %d\nsalle ==%d\n\n", index, len);
		if (room[end].liens->next == NULL)
			break ;
		room[end].liens = room[end].liens->next;
	}
	room[end].liens = room[end].liens->begin;
	ft_printf("\n-------\n");
}
