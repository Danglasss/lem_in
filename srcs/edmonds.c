/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 08:48:54 by damboule          #+#    #+#             */
/*   Updated: 2020/01/10 10:57:49 by danglass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	positif_link(t_salle *room, unsigned long index, t_stack *find)
{
	if (index == find->index_start)
		return ;
	room[index].liens = room[index].liens->begin;		
	while ((unsigned long)room[index].liens->out != room[index].salle_prev[0])
		room[index].liens = room[index].liens->next;
	if ((unsigned long)room[index].liens->out != find->index_end && (unsigned long)room[index].liens->out != find->index_start)
		room[index].liens->open = 1;
}

void	negatif_link(t_salle *room, unsigned long index,  unsigned long tmp, t_stack *find)
{
	room[index].liens = room[index].liens->begin;		
	while ((unsigned long)room[index].liens->out != tmp)
		room[index].liens = room[index].liens->next;
	//if ((unsigned long)room[index].liens->out != find->index_end/* && (unsigned long)room[index].liens->out != find->index_start*/)
		room[index].liens->open = -1;
	//if (find->index_start == index)
	//	ft_printf("\nTOUCH\n");
}

void	lucky_link(t_salle *room, unsigned long index,  unsigned long tmp, t_stack *find)
{
	room[index].liens = room[index].liens->begin;		
	while ((unsigned long)room[index].liens->out != tmp)
	{
		if (room[index].liens->next == NULL)
			break ;
		room[index].liens = room[index].liens->next;
	}
	room[index].liens->open = 3;
	room[index].liens = room[index].liens->begin;
}

void	neutral_link(t_salle *room, unsigned long index,  unsigned long tmp, t_stack *find)
{
	if (len_out(room[index].liens, 1) < 3)
		return ;
	room[index].liens = room[index].liens->begin;		
	while (room[index].liens != NULL)
	{
		if ((unsigned long)room[index].liens->out != tmp &&
		(unsigned long)room[index].liens->out != room[index].salle_prev[0]
		&& (unsigned long)room[index].liens->out != 0)
			lucky_link(room, (unsigned long)room[index].liens->out, index, find);
		if (room[index].liens->next == NULL)
			break ;
		room[index].liens = room[index].liens->next;
	}
	room[index].liens = room[index].liens->begin;
}

void	path(t_salle *room, t_stack *find, unsigned long end, unsigned long salle_prev)
{
	unsigned long index;
	unsigned long tmp;
	unsigned long sale;
	
	index = end;
	while (index != find->index_start)
	{
		//ft_printf("salle : %s\n", room[index].salle);
		if (index != find->index_end)
		{
			negatif_link(room, index, tmp, find);
			positif_link(room, index, find);
			neutral_link(room, index, tmp, find);
		}
		tmp = index;
		if (index == find->index_end)
		{
			index = salle_prev;
			continue ;
		}
		index = room[index].salle_prev[0];
	}
	//ft_printf("%s ", room[index].salle);
	negatif_link(room, index, tmp, find);
	positif_link(room, index, find);
}

void	findpath(t_salle *room, t_stack *find, unsigned long end)
{
	int len;
	int index;

	len = 0;
	index = 0;
	//ft_printf("\n\n");
	path(room, find, find->index_end, room[end].salle_prev[0]);
	while (room[end].liens->salle_prev != 0)
	{
		path(room, find, find->index_end, room[end].liens->salle_prev);
		//ft_printf("\n\n");
		if (room[end].liens->next == NULL)
			break ;
		room[end].liens = room[end].liens->next;
	}
	room[end].liens = room[end].liens->begin;
	//ft_printf("\n\n");
}

void	clear(t_salle *room, t_stack *find, t_out *index)
{
	int len;

	index = index->begin;
	len = len_out(index, 1) - 1;
	while (len)
	{ 
		room[(unsigned long)index->out].free = 0;
		len = len - 1;
		index = index->next;
	}
}

void	ft_clean(t_salle *room, t_out *index)
{
	int len_room;
	int len_lien;

	index = index->begin;
	len_room = len_out(index, 1) - 1;
	while (len_room)
	{
		len_lien = len_out(room[(unsigned long)index->out].liens, 1) - 1;
		room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->begin;		
		while (len_lien)
		{
			//ft_printf("salle : %s || ", room[(unsigned long)room[(unsigned long)index->out].liens->out].salle);
			//ft_printf("liens : %d\n", room[(unsigned long)index->out].liens->open);
			room[(unsigned long)index->out].liens->open = 0;
			if (room[(unsigned long)index->out].liens->next == NULL)
				len_lien = 0;
			else
				room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->next;
		}
		room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->begin;
		index = index->next;
		len_room--;
	}
	index = index->begin;
}

void	ft_reset(t_salle *room, t_out *index)
{
	int len_room;
	int len_lien;

	index = index->begin;
	len_room = len_out(index, 1) - 1;
	while (len_room)
	{
		len_lien = len_out(room[(unsigned long)index->out].liens, 1) - 1;
		room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->begin;		
		while (len_lien)
		{
			room[(unsigned long)index->out].salle_prev[1] = 0;
			if (room[(unsigned long)index->out].liens->next == NULL)
				len_lien = 0;
			else
				room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->next;
		}
		room[(unsigned long)index->out].liens = room[(unsigned long)index->out].liens->begin;
		index = index->next;
		len_room--;
	}
	index = index->begin;
}

int		Bhandari(t_salle *room, t_stack *find, t_out *index)
{
	int		bhandari_state;
	int len = 0;

	bhandari_state = 0;
	while (bhandari_state < 1)
	{
		find->finish = 0;
		bhandari_state = algo(room, find, index);
		if (find->finish == 0)
			break ;
		ft_reset(room, index);	
		if (bhandari_state == -1)
		{
			ft_clean(room, index);
			room[find->index_end].salle_prev[0] = 0;
			while (room[find->index_end].liens->salle_prev != 0)
			{
				room[find->index_end].liens->salle_prev = 0;
				if (room[find->index_end].liens->next == NULL)
					break ;
				room[find->index_end].liens = room[find->index_end].liens->next;
			}
			room[find->index_end].liens->salle_prev = 0;
			room[find->index_end].liens = room[find->index_end].liens->begin;
		}
		len++;
	}
	return (1);
}
