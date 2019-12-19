/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:41:22 by damboule          #+#    #+#             */
/*   Updated: 2019/10/18 17:35:45 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void		ft_reset_repertition(t_pos *pos)
{
	pos = pos->begin;
	while (pos != NULL)
	{
		pos->fourmies = 0;
		pos->salle = 0;
		pos->instruction = 0;
		if (pos->next == NULL)
			break ;
		pos = pos->next;
	}
}

int			ft_max(t_pos *path)
{
	int ret;

	ret = 0;
	while (path != NULL)
	{
		if (ret < path->salle)
			ret = path->salle;
		path = path->next;
	}
	return (ret);
}

int		f_equal(t_pos *path, int fourmie)
{
	int		instruction;
	int		nb_ways;
	int		equal;
	int		reste;
	t_pos	*temp;

	temp = path;
	nb_ways = len_pos(temp, 0);
	equal = fourmie / nb_ways;
	reste = fourmie % nb_ways;
	instruction = 0;
	while (path != NULL)
	{
		path->fourmies += equal;
		path->instruction += equal;
		if (instruction < path->instruction)
			instruction = path->instruction;
		if (reste - 1 >= 0)
		{
			reste = reste - 1;
			path->fourmies += 1;
			path->instruction += 1;
			instruction = path->instruction;
		}
		path = path->next;
	}
	return (instruction);
}

int			f_repartition(t_pos *path)
{
	int		ret;
	int		fourmie;

	ret = ft_max(path);
	fourmie = 0;
	while (path != NULL)
	{
		//ft_printf("0\n");
		if (ret == path->salle && path->fourmies == 0)
		{
			//ft_printf("1\n");
			fourmie += 1;
			path->fourmies = 1;
			path->instruction = path->fourmies + path->salle;
		}
		else if (ret > path->salle)
		{
			//ft_printf("2\n");
			fourmie += (ret - path->salle) + 1;
			path->fourmies = (ret - path->salle) + 1;
			path->instruction = path->fourmies + path->salle;
		}
		path = path->next;
	}
	return (fourmie);
}
