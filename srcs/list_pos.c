/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:34:14 by damboule          #+#    #+#             */
/*   Updated: 2020/02/01 18:19:50 by damboule         ###   ########.fr       */
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
	(*stack)->index = (unsigned long)(*liens)->out;
	(*liens) = (*liens)->next;
	if ((*stack)->next == NULL)
		out_add_tolist(stack, NULL, 1);
	else
		(*stack) = (*stack)->next;
}

void	clean_current(t_snapshot **list)
{
	(*list)->banned = (*list)->banned->begin;
	while ((*list))
	{
		(*list)->banned->room1 = 0;
		(*list)->banned->room2 = 0;
		if ((*list)->banned->next == NULL)
			break ;
		(*list)->banned = (*list)->banned->next;
	}
}