/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 11:41:27 by dygouin          #+#    #+#             */
/*   Updated: 2020/01/30 15:06:15 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	leaks_info(t_stack *info)
{
	if (info->n_end != NULL)
	{
		free(info->n_end);
		info->n_end = NULL;
	}
	if (info->n_start)
	{
		free(info->n_start);
		info->n_start = NULL;
	}
	free(info);
	info = NULL;
}

void	leaks_out(t_out *leaks)
{
	t_out	*tmp;

	leaks = leaks->begin;
	while (leaks != NULL)
	{
		//if (leaks->out != NULL)
		//  free(leaks->out);
		leaks->begin = NULL;
		leaks->prev = NULL;
		leaks->out = NULL;
		tmp = leaks->next;
		free(leaks);
		leaks = tmp;
		tmp = NULL;
	}
}

void	leaks_salle(t_salle *s, int a, t_out *i)
{
	int	index;

	index = 0;
	i = i->begin;
	while (i->out != NULL)
	{
		leaks_out(s[(unsigned long)i->out].liens);
		free(s[(unsigned long)i->out].salle);
		s[(unsigned long)i->out].salle = NULL;
		i = i->next;
	}
	while (index < a)
	{
		free(s);
		s = NULL;
		index++;
	}
}
