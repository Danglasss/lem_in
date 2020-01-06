/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:01:59 by danglass          #+#    #+#             */
/*   Updated: 2020/01/03 17:09:37 by danglass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	turnpath(t_salle *room, t_stack *find)
{
	unsigned long index;
	unsigned long tmp;

	index = find->index_end;
	while (index != find->index_start)
	{
		tmp = index;
		index = room[index].salle_prev[0];
	}
}

void	affichage(t_salle *room, t_stack *find)
{
	turnpath(room, find);
}
