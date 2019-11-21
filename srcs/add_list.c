/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:37:43 by damboule          #+#    #+#             */
/*   Updated: 2019/10/09 05:20:31 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	pos_add_tolist(t_pos **list, t_out *data, int truth)
{
	t_pos	*n_elist;

	if ((*list)->ways == NULL && truth == 0)
	{
		if (data != NULL)
			outfill_out(&(*list)->ways, data);
		return ;
	}
	pos_init(&n_elist, 1);
	(*n_elist).begin = (*list)->begin;
	if (data != NULL)
		outfill_out(&n_elist->ways, data);
	if ((*list)->next != NULL)
		n_elist->next = (*list)->next;
	n_elist->prev = (*list);
	(*list)->next = n_elist;
	if (truth == 1 || n_elist->ways != NULL)
		(*list) = n_elist;
}

void	out_add_tolist(t_out **list, char *data, int truth)
{
	t_out	*n_elist;

	if (truth == 0 && (*list)->out == NULL)
	{
		if (data != NULL)
			(*list)->out = ft_strdup((char *)data, 0);
		return ;
	}
	out_init(&n_elist, 1);
	if (data != NULL)
		n_elist->out = ft_strdup((char *)data, 0);
	else
		n_elist->out = data;
	n_elist->begin = (*list)->begin;
	n_elist->prev = (*list);
	(*list)->next = n_elist;
	if (truth == 1 || n_elist->out != NULL)
		(*list) = n_elist;
}

void	t_data(t_out **list, char **data)
{
	int		i;

	i = 0;
	if (!data)
		return ;
	while (data[i] != 0)
		out_add_tolist(list, data[i++], 1);
}

t_out	*out_cpy(t_out *src)
{
	t_out	*n_list;

	out_init(&n_list, 0);
	while (src != NULL)
	{
		out_add_tolist(&n_list, src->out, 1);
		src = src->next;
	}
	return (n_list);
}

void	outfill_out(t_out **dst, t_out *src)
{
	while (src != NULL)
	{
		out_add_tolist(dst, src->out, 0);
		src = src->next;
	}
}