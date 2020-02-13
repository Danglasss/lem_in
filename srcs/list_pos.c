/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:34:14 by damboule          #+#    #+#             */
/*   Updated: 2020/02/13 14:04:10 by damboule         ###   ########.fr       */
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

void	outn_prev(t_out **out, unsigned int n)
{
	unsigned int	count;

	count = 0;
	while (count++ < n)
		(*out) = (*out)->prev;
}

int		len_out(t_out *list, int origin)
{
	int		i;

	i = 0;
	if (origin == 1)
		list = list->begin;
	while (list != NULL && i++ > -1)
		list = list->next;
	return (i);
}
