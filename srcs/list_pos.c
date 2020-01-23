/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:34:14 by damboule          #+#    #+#             */
/*   Updated: 2020/01/23 09:11:45 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	out_end(t_out **list)
{
	if ((*list) == NULL || (*list)->next == NULL)
		return ;
	while ((*list)->next != NULL)
		(*list) = (*list)->next;
	(*list) = (*list)->prev;
}

void	pos_end(t_pos **list)
{
	if ((*list) == NULL || (*list)->next == NULL)
		return ;
	while ((*list)->next != NULL)
		(*list) = (*list)->next;
	(*list) = (*list)->prev;
}

void	npos_next(t_pos **list, unsigned int count)
{
	unsigned int	i;

	i = 0;
	while (i < count)
		(*list) = (*list)->next;
}

void	nout_next(t_out **list, unsigned int count)
{
	unsigned int	i;

	i = 0;
	while (i++ < count && (*list)->next != NULL)
	{
		(*list) = (*list)->next;
	}
}

void	next(t_out **liens, t_out **stack)
{
	(*liens) = (*liens)->next;
	if ((*stack)->next == NULL)
		out_add_tolist(stack, NULL, 1);
	else
		(*stack) = (*stack)->next;
}
