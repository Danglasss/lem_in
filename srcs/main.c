/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:10:28 by dygouin          #+#    #+#             */
/*   Updated: 2020/01/30 15:06:39 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	way_back(t_out *p_list, t_salle *rooms)
{
	p_list = p_list->begin;
	while (p_list->out)
	{
		rooms[(int)p_list->out].liens = rooms[(int)p_list->out].liens->begin;
		if (p_list->next != NULL)
			p_list = p_list->next;
		else
			break ;
	}
	p_list = p_list->begin;
}

int		ft_error(t_salle *rooms, t_stack *info)
{
	if (info->n_end == NULL || info->n_start == NULL || info->fourmies <= 0
		|| rooms[t_hash(info->n_start, rooms)].liens->begin->out == NULL
		|| rooms[t_hash(info->n_end, rooms)].liens->begin->out == NULL)
		return (1);
	return (0);
}

int		ft_main_algo(t_out *reads, t_out *index, t_pos *path, t_pos *pos)
{
	t_salle		*rooms;
	t_stack		*info;

	stack_room_init(&info, &rooms);
	check_insert(&reads, &index, &rooms, info);
	//ft_printread(reads->begin);
	if (ft_error(rooms, info))
		return (write(2, "ERROR\n", 6));
	way_back(index, rooms);
	clean_map(rooms, info, index);
	bhandari(rooms, info, index);
	affichage(rooms, info);
	path = path->begin;
	//t_end(info, rooms, path->begin);
	//leaks_salle(rooms, t_size, index);
	//leaks_info(info);
	init_leak(&reads, &index, &path, &pos);
	//while (1);
	// pos deja free dans ft_edmonds;
	return (1);
}

int		main(void)
{
	t_out		*reads;
	t_out		*index;
	t_pos		*pos;
	t_pos		*path;

	out_init(&reads, 0);
	out_init(&index, 0);
	pos_init(&path, 0);
	pos_init(&pos, 0);
	ft_main_algo(reads, index, path, pos);
	return (0);
}
