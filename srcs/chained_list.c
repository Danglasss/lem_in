/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:19:28 by dygouin           #+#    #+#             */
/*   Updated: 2020/02/15 18:29:34 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	cpy_length(t_out **dst, t_out *src, t_out **begin)
{
	(*dst) = (*dst)->begin;
	src = src->begin;
	while (src && (*dst))
	{
		(*dst)->index = src->index;
		src->index = 0;
		if ((*dst)->next == NULL)
			out_add_tolist(dst, NULL, 1);
		else
			(*dst) = (*dst)->next;
		src = src->next;
	}
	(*dst) = (*dst)->begin;
	(*begin) = (*begin)->begin;
}

void	cases_cpy(t_cases **dst, t_cases *src)
{
	(*dst) = (*dst)->begin;
	src = src->begin;
	while (src)
	{
		(*dst)->index = src->index;
		if ((*dst)->next == NULL)
			cases_add_tolist(dst, 0);
		else
			(*dst) = (*dst)->next;
		if (src->next == NULL)
			break ;
		src = src->next;
	}
}

void	path_cpy(t_path **best, t_path *curr, int len)
{
	int index;

	index = 0;
	while (index < len)
	{
		(*best)[index].lines = curr[index].lines;
		(*best)[index].ants = curr[index].ants;
		(*best)[index].length = curr[index].length;
		cases_cpy(&(*best)[index].cases, curr[index].cases);
		index++;
	}
}

void	clean_cases(t_cases **room)
{
	(*room) = (*room)->begin;
	while ((*room))
	{
		(*room)->index = 0;
		if ((*room)->next == NULL)
			break ;
		(*room) = (*room)->next;
	}
}

void	clean_current(t_path **current, int len)
{
	int index;

	index = 0;
	while (index < len)
	{
		clean_cases(&(*current)[index].cases);
		(*current)[index].lines = 0;
		(*current)[index].ants = 0;
		(*current)[index].length = 0;
		index++;
	}
}
