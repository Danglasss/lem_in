/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:10:28 by dygouin           #+#    #+#             */
/*   Updated: 2020/02/12 17:07:34 by dygouin          ###   ########.fr       */
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
		|| rooms[t_hash(info->n_end, rooms)].liens->begin->out == NULL
		|| info->error == -1)
		return (1);
	return (0);
}

int		ft_main_algo(t_out *reads, t_out *index)
{
	t_salle		*rooms;
	t_stack		*info;
	t_path		*best_shot;

	stack_room_init(&info, &rooms);
	check_insert(&reads, &index, &rooms, info);
	leaks_out(reads, 1);
	if (ft_error(rooms, info))
		return (write(2, "ERROR\n", 6));

	way_back(index, rooms);
	clean_map(rooms, info, index);
	path_init(&best_shot, rooms, info);
	bhandari(rooms, info, index, best_shot);
	affichage(rooms, info);

	leaks_path(best_shot, len_out(rooms[info->index_end].liens, 1));
	leaks_salle(rooms, T_SIZE, index);
	leaks_out(index, 0);
	leaks_info(info);
	
	//while (1);

	return (1);
}

int		main(void)
{
	t_out		*reads;
	t_out		*index;

	out_init(&reads, 0);
	out_init(&index, 0);
	ft_main_algo(reads, index);
	return (0);
}
