/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repartition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 10:16:23 by damboule          #+#    #+#             */
/*   Updated: 2019/09/25 14:30:33 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	inti(t_struct *way, t_stack *find, int max)
{
	int index;

	index = 0;
	way->nb = find->ways;
	while (index < max)
	{
		way[index].fourmies = 0;
		way[index].instruct = 0;
		index++;
	}
}

int		fonc(t_stack *find, t_salle *room)
{
	int	resultat;
	int	start;
	int	end;

	start = len_out(room[t_hash(find->n_start, room)].liens, 1) - 1;
	end = len_out(room[t_hash(find->n_end, room)].liens, 1) - 1;
	//ft_printf("start == %d || end == %d\n\n", start, end);
	resultat = start;
	if (start > end)
		resultat = start;
	if (resultat == 0)
		resultat = 1;
	return (resultat);
}

/*
 ** Modifier reste avec nouvelle repartition
 ** Fichier dans affichage
 */

int		ft_equaliser(t_struct *way, int fourmies, int path, t_stack *find)
{
	int	equal;
	int	reste;
	int	index;

	(void)find;
	index = -1;
	equal = fourmies / path;
	reste = fourmies % path;
	while (++index < path)
	{
		way[index].fourmies += equal;
		way[index].instruct += equal;
		if (reste-- >= 0)
		{
			way[index].fourmies += 1;
			way[index].instruct += 1;
		}
	}
	way[0].fourmies -= 1;
	way[0].instruct -= 1;
	return (way[0].instruct);
}

int		repartition(t_struct *way, t_stack *find, int max_path)
{
	int	len;
	int	fourmies;
	int	last;

	len = 0;
	fourmies = find[0].fourmies - 1;
	inti(way, find, max_path);
	last = way[0].nb - 1;
	way[last].salle = find[0].salle;
	way[last].instruct = find[0].salle;
	while (len < last)
	{
		way[len].fourmies = way[last].instruct - way[len].salle;
		way[len].instruct = way[len].fourmies + way[len].salle;
		fourmies -= way[len].fourmies;
		len++;
	}
	return (ft_equaliser(way, fourmies, way[0].nb, find));
}

int		ft_calculpath(t_struct *way, t_stack *find, int max_path)
{
	int	fourmies;
	int	instruct;
	int	resultat;

	if (max_path == way->nb)
		return (0);
	if (way->nb >= 2)
	{
		instruct = repartition(way, find, max_path);
		resultat = instruct - find[0].salle;
		return (resultat);
	}
	fourmies = find->fourmies - 1;
	instruct = find->salle + fourmies;
	resultat = instruct - find->salle;
	return (resultat);
}
