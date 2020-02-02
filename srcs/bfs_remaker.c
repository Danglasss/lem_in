/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_remaker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:19:23 by damboule          #+#    #+#             */
/*   Updated: 2020/02/02 19:51:40 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	ft_dellink(t_salle *room, unsigned long index, unsigned long delink)
{
	room[index].liens = room[index].liens->begin;
	while ((unsigned long)room[index].liens->out != delink)
	{
		if (room[index].liens->next == NULL)
			break ;
		room[index].liens = room[index].liens->next;
	}
	if ((unsigned long)room[index].liens->out == delink)
		room[index].liens->del[0] = 1;
}

void	apply_banned(t_salle *room, t_banned *banned)
{
	banned = banned->begin;
	while (banned)
	{
		ft_printf("%s\n%s\n", room[banned->room1].salle, room[banned->room2].salle);
		ft_dellink(room, banned->room1, banned->room2);
		ft_dellink(room, banned->room2, banned->room1);
		if (banned->next == NULL)
			break ;
		banned = banned->next;
	}
	banned = banned->begin;
}

void	bfs_remaker(t_salle *room, t_stack *find, t_out *index, t_snapshot	*best_shot)
{
	if (find->counter_del == -1)
		return;
	ft_clean_end(room, find);
	ft_clean(room, index);
	apply_banned(room, best_shot->banned);
	exit(1);
}