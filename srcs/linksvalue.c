/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linksvalue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 09:17:41 by damboule          #+#    #+#             */
/*   Updated: 2020/01/28 16:27:12 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	positif_link(t_salle *room, unsigned long index, t_stack *find)
{
	if (index == find->index_start)
		return ;
	//ft_printf("A\n");	
	room[index].liens = room[index].liens->begin;
	//ft_printf("B\n");	
	while ((unsigned long)room[index].liens->out != room[index].salle_prev[0])
	{
		//ft_printf("salle prev == %s || liens == %s || index == %d\n", room[room[index].salle_prev[0]].salle, room[(unsigned long)room[index].liens->out].salle, index);
		room[index].liens = room[index].liens->next;
		//ft_printf("salle prev == %s || liens == %s\n", room[room[index].salle_prev[0]].salle, room[(unsigned long)room[index].liens->out].salle);
		//if (room[index].liens->next == NULL)
		//	break ;
	}
	//ft_printf("salle prev == %s || liens == %s\n", room[room[index].salle_prev[0]].salle, room[(unsigned long)room[index].liens->out].salle);
	//ft_printf("C\n");	
	if ((unsigned long)room[index].liens->out != find->index_end && (unsigned long)room[index].liens->out != find->index_start)
		room[index].liens->open = 1;
}

void	negatif_link(t_salle *room, unsigned long index,  unsigned long tmp, t_stack *find)
{
	room[index].liens = room[index].liens->begin;
	while ((unsigned long)room[index].liens->out != tmp)
		room[index].liens = room[index].liens->next;
	room[index].liens->open = -1;
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
	//ft_printf("%s\n", room[index].salle);
	//ft_printf("%s\n", room[(unsigned long)room[index].liens->out].salle);
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
		{
			lucky_link(room, (unsigned long)room[index].liens->out, index, find);
			room[index].liens->open = 3;
		}
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
		//ft_printf("salle == %s\n", room[index].salle);
		//print_lien(room[index].liens->begin, room);
		if (index != find->index_end)
		{
			//ft_printf("0\n");
			negatif_link(room, index, tmp, find);
			//ft_printf("1\n");
			positif_link(room, index, find);
			//ft_printf("2\n");
			neutral_link(room, index, tmp, find);
			//ft_printf("3\n");
		}
		tmp = index;
		if (index == find->index_end)
		{
			index = salle_prev;
			continue ;
		}
		index = room[index].salle_prev[0];
	}
	negatif_link(room, index, tmp, find);
	positif_link(room, index, find);
}