/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:52:35 by dygouin           #+#    #+#             */
/*   Updated: 2020/02/12 16:53:42 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

unsigned long	s_collision(char *to_hash, t_salle *room,
		unsigned long hashed_s)
{
	if (room[hashed_s + 7].salle == NULL
			|| !ft_strcmp(room[hashed_s + 7].salle, to_hash))
		return (hashed_s + 7);
	else if (room[hashed_s - 7].salle == NULL
			|| !ft_strcmp(room[hashed_s - 7].salle, to_hash))
		return (hashed_s - 7);
	else if (room[hashed_s + 8].salle == NULL
			|| !ft_strcmp(room[hashed_s + 8].salle, to_hash))
		return (hashed_s + 8);
	else if (room[hashed_s - 8].salle == NULL
			|| !ft_strcmp(room[hashed_s - 8].salle, to_hash))
		return (hashed_s - 8);
	else if (room[hashed_s + 9].salle == NULL
			|| !ft_strcmp(room[hashed_s + 9].salle, to_hash))
		return (hashed_s + 9);
	else if (room[hashed_s - 9].salle == NULL
			|| !ft_strcmp(room[hashed_s - 9].salle, to_hash))
		return (hashed_s - 9);
	return (hashed_s);
}

unsigned long	n_collision(char *to_hash, t_salle *room,
		unsigned long hashed_s)
{
	if (room[hashed_s - 5].salle == NULL
			|| !ft_strcmp(room[hashed_s - 5].salle, to_hash))
		return (hashed_s - 5);
	else if (room[hashed_s + 5].salle == NULL
			|| !ft_strcmp(room[hashed_s + 5].salle, to_hash))
		return (hashed_s + 5);
	else if (room[hashed_s + 6].salle == NULL
			|| !ft_strcmp(room[hashed_s + 6].salle, to_hash))
		return (hashed_s + 6);
	else if (room[hashed_s - 6].salle == NULL
			|| !ft_strcmp(room[hashed_s - 6].salle, to_hash))
		return (hashed_s - 6);
	return (s_collision(to_hash, room, hashed_s));
}

unsigned long	collision(char *to_hash, t_salle *room,
unsigned long hashed_s)
{
	if ((room[hashed_s - 1].salle == NULL
				|| !ft_strcmp(room[hashed_s - 1].salle, to_hash)))
		return (hashed_s - 1);
	else if (room[hashed_s + 1].salle == NULL
			|| !ft_strcmp(room[hashed_s + 1].salle, to_hash))
		return (hashed_s + 1);
	else if (room[hashed_s + 2].salle == NULL
			|| !ft_strcmp(room[hashed_s + 2].salle, to_hash))
		return (hashed_s + 2);
	else if (room[hashed_s - 2].salle == NULL
			|| !ft_strcmp(room[hashed_s - 2].salle, to_hash))
		return (hashed_s - 2);
	else if (room[hashed_s + 3].salle == NULL
			|| !ft_strcmp(room[hashed_s + 3].salle, to_hash))
		return (hashed_s + 3);
	else if (room[hashed_s - 3].salle == NULL
			|| !ft_strcmp(room[hashed_s - 3].salle, to_hash))
		return (hashed_s - 3);
	else if (room[hashed_s + 4].salle == NULL
			|| !ft_strcmp(room[hashed_s + 4].salle, to_hash))
		return (hashed_s + 4);
	else if (room[hashed_s - 4].salle == NULL
			|| !ft_strcmp(room[hashed_s - 4].salle, to_hash))
		return (hashed_s - 4);
	return (n_collision(to_hash, room, hashed_s));
}

unsigned long	col(char *to_hash, t_salle *room,
		unsigned long hashed_s)
{
	if (room[hashed_s + 1].salle == NULL
			|| !ft_strcmp(room[hashed_s + 1].salle, to_hash))
		return (hashed_s + 1);
	else if (room[hashed_s + 2].salle == NULL
			|| !ft_strcmp(room[hashed_s + 2].salle, to_hash))
		return (hashed_s + 2);
	else if (room[hashed_s + 3].salle == NULL
			|| !ft_strcmp(room[hashed_s + 3].salle, to_hash))
		return (hashed_s + 3);
	else if (room[hashed_s + 4].salle == NULL
			|| !ft_strcmp(room[hashed_s + 4].salle, to_hash))
		return (hashed_s + 4);
	return (n_collision(to_hash, room, hashed_s));
}

unsigned long	t_hash(char *to_hash, t_salle *room)
{
	unsigned long	hashed_s;
	int				i;
	int				m;

	i = 0;
	m = 1;
	hashed_s = 0;
	while (to_hash[i])
	{
		hashed_s += to_hash[i];
		hashed_s += hashed_s << 10;
		hashed_s ^= hashed_s >> 6;
		i++;
	}
	hashed_s += hashed_s << 3;
	hashed_s ^= hashed_s >> 11;
	hashed_s += hashed_s << 15;
	hashed_s %= T_SIZE;
	if (hashed_s == 0)
		return (col(to_hash, room, hashed_s));
	if ((room[hashed_s].salle != NULL &&
			ft_strcmp(room[hashed_s].salle, to_hash)))
		return (collision(to_hash, room, hashed_s));
	return (hashed_s);
}
