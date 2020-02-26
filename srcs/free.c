/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:26:45 by damboule          #+#    #+#             */
/*   Updated: 2020/02/26 16:18:07 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_all_l(t_out **list)
{
	t_out	*tmp;

	while (list != NULL && (*list) != NULL)
	{
		if ((*list)->out != NULL)
			free((*list)->out);
		(*list)->begin = NULL;
		(*list)->out = NULL;
		tmp = (*list)->next;
		(*list)->next = NULL;
		free((*list));
		(*list) = tmp;
	}
	(*list) = NULL;
}

int		free_all(char **str, int truth)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i++] = NULL;
	}
	free(str);
	str = NULL;
	if (truth == 1)
	{
		ft_putstr_fd("ERROR", 2);
		exit(0);
	}
	return (1);
}

int		free_reset(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (1);
}
