/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 11:41:27 by dygouin           #+#    #+#             */
/*   Updated: 2020/02/12 15:59:35 by dygouin          ###   ########.fr       */
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

void	leaks_out(t_out *leaks, int i)
{
	t_out	*tmp;

	leaks = leaks->begin;
	while (leaks != NULL)
	{
		if (i == 1)
			free(leaks->out);
		leaks->begin = NULL;
		leaks->prev = NULL;
		leaks->out = NULL;
		tmp = leaks->next;
		free(leaks);
		leaks = tmp;
		tmp = NULL;
	}
}

void	leaks_salle(t_salle *room, int len, t_out *index)
{
	unsigned long	a;

	a = 0;
	index = index->begin;
	while (index->out != NULL)
	{
		leaks_out(room[(unsigned long)index->out].liens, 0);
		free(room[(unsigned long)index->out].salle);
		room[(unsigned long)index->out].salle = NULL;
		index = index->next;
	}
	free(room);
	room = NULL;
}

void	leaks_cases(t_cases *list)
{
	t_cases *tmp;

	list = list->begin;
	while (list != NULL)
	{
		list->begin = NULL;
		tmp = list->next;
		free(list);
		list = tmp;
		tmp = NULL;
	}
}

void	leaks_path(t_path *path, int len)
{
	int		index;

	index = 0;
	while (index < len)
	{
		leaks_cases(path[index].cases);
		index++;
	}
	free(path);
	path = NULL;
}
