/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:01:59 by danglass          #+#    #+#             */
/*   Updated: 2020/01/06 15:17:27 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	turnpath(t_salle *room, t_stack *find)
{
	unsigned long salle;
	unsigned long stack;
	unsigned long tmp;

	stack = room[find->index_end].salle_prev[0];
	salle = find->index_end;
	while (salle != find->index_start)
	{	
		tmp = room[stack].salle_prev[0];
		room[stack].salle_prev[0] = salle;
		salle = stack;
		stack = tmp;
	}
}

void	affichage(t_salle *room, t_stack *find)
{
	turnpath(room, find);
}
