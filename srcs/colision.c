/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:41:22 by damboule          #+#    #+#             */
/*   Updated: 2019/10/09 11:04:51 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void		ft_take_path(t_pos *path)
{
	path = path->begin;
	while (path != NULL)
	{
		path->colision = path->colision->begin;
		ft_printf("%d\n", path->id);
		while (path->colision != NULL)
		{
			ft_printf("colision ==> %lu\n", path->colision->touch);
			if (path->colision->next == NULL)
				break ;
			path->colision = path->colision->next;
		}
		exit(1);
		if (path->next == NULL)
			break ;
		path = path->next;
	}
	//print_allpos(path->begin, room);
}

void		ft_room_colision(t_pos *path, t_salle *room)
{
	unsigned long	index;

	//ft_list_path(&path->begin/*, temp*/);
	path = path->begin;
	while (path != NULL)
	{
		path->ways = path->ways->begin;
		ft_printf("\nID == %d\n", path->id);
		out_init(&path->colision, 0);		
		while (path->ways != NULL)
		{
			ft_printf("\nSalle == %s\n", room[(unsigned long)path->ways->out].salle);
			index = (unsigned long)path->ways->out;
			room[index].collision = room[index].collision->begin;
			while (room[index].collision != NULL)
			{
				ft_printf("%lu\n", room[index].collision->touch);
				if (path->colision == NULL)
					path->colision->touch = room[index].collision->touch;
				else
				{
					out_add_tolist(&path->colision, NULL, 1);
					path->colision->touch = room[index].collision->touch;
				}
				if (room[index].collision->next == NULL)
					break ;
				room[index].collision = room[index].collision->next;
			}
			if (path->ways->next == NULL)
				break ;
			path->ways = path->ways->next;
		}
		path = path->next;
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

void		f_equal(t_pos *path, int fourmie)
{
	int		nb_ways;
	int		equal;
	int		reste;
	t_pos	*temp;

	temp = path;
	nb_ways = len_pos(temp, 0);
	equal = fourmie / nb_ways;
	reste = fourmie % nb_ways;
	while (path != NULL)
	{
		path->fourmies += equal;
		path->instruction += equal;
		if (reste - 1 >= 0)
		{
			reste = reste - 1;
			path->fourmies += 1;
			path->instruction += 1;
		}
		path = path->next;
	}
}

int			f_repartition(t_pos *path)
{
	int		ret;
	int		fourmie;

	ret = ft_max(path);
	fourmie = 0;
	while (path != NULL)
	{
		if (ret == path->salle && path->fourmies == 0)
		{
			fourmie += 1;
			path->fourmies = 1;
			path->instruction = path->fourmies + path->salle;
		}
		else if (ret > path->salle)
		{
			fourmie += (ret - path->salle) + 1;
			path->fourmies = (ret - path->salle) + 1;
			path->instruction = path->fourmies + path->salle;
		}
		path = path->next;
	}
	return (fourmie);
}
