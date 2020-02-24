/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:58:39 by damboule          #+#    #+#             */
/*   Updated: 2020/02/22 18:58:10 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		p_doubleroom(t_salle *room, t_stack *find, t_out *read)
{
	int i;
	int	stop;

	stop = 0;
	i = 1;
	while (room[find->index_start].liens->next != NULL)
	{
		if ((unsigned long)room[find->index_start].liens->out ==
				find->index_end)
		{
			stop = 1;
		}
		room[find->index_start].liens =
			room[find->index_start].liens->next;
	}
	if (stop == 0)
		return (1);
	ft_printread(read);
	while (i <= find->fourmies)
	{
		ft_printf("L%d-%s ", i, room[find->index_end].salle);
		i++;
	}
	ft_printf("\n");
	return (0);
}

int		p_salle(t_salle *room, t_stack *find,
		unsigned long salle_prev, t_cases *current)
{
	unsigned long	index;
	int				len;

	index = find->index_end;
	len = 0;
	while (index != find->index_start)
	{
		if (current->index == index)
			current = current->next;
		else
			cases_add_tolist(&current, index);
		len++;
		if (index == find->index_end)
		{
			index = salle_prev;
			continue ;
		}
		index = room[index].salle_prev[0];
	}
	if (current->index == index)
		current = current->next;
	else
		cases_add_tolist(&current, index);
	return (len);
}

void	printpath(t_salle *room, t_stack *find, t_path *current)
{
	int				curr;
	unsigned long	end;
	int				len;
	int				index;

	end = find->index_end;
	curr = 0;
	index = 1;
	len = p_salle(room, find, room[end].salle_prev[0],
			current[curr].cases->begin);
	room[end].nb_salle = len;
	room[end].liens = room[end].liens->begin;
	while (room[end].liens->salle_prev != 0)
	{
		curr++;
		index++;
		len = p_salle(room, find, room[end].liens->salle_prev,
				current[curr].cases->begin);
		room[end].liens->nb_salle = len;
		if (room[end].liens->next == NULL)
			break ;
		room[end].liens = room[end].liens->next;
	}
	room[end].liens = room[end].liens->begin;
}
