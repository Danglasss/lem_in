/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:15:56 by dygouin           #+#    #+#             */
/*   Updated: 2020/02/11 10:47:23 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
static int		special_insert(t_salle **rooms, t_stack *info, t_out **index,
		t_out **reads)
{
	char	*l_line;
	char	**splited;

	l_line = NULL;
	get_next_line(0, &l_line);
	out_add_tolist(reads, l_line, 1);
	if (check_rformat(l_line) == -1 && free_reset(l_line))
		return (0);
	splited = ft_strsplit(l_line, ' ');
	if (create_room(*rooms, splited[0], index) == -1)
		return (-1);
	if (info->ways == 0)
	{
		info->n_start = ft_strdup(splited[0], 0);
		info->index_start = t_hash(splited[0], *rooms);
	}
	if (info->ways == 1)
	{
		info->n_end = ft_strdup(splited[0], 0);
		info->index_end = t_hash(splited[0], *rooms);
	}
	free_reset(l_line);
	free_all(splited, 0);
	return (1);
}

static int		check_hash(t_stack *info, t_out **index, t_salle **rooms,
		t_out **reads)
{
	if (((char *)(*reads)->out)[1] != '#' || ft_strncmp(((char *)(*reads)->out), "###", 3) == 0)
		return (1);
	else if (info->fourmies == -1)
		return (0);
	else if (ft_strcmp(((char *)(*reads)->out), "##start") == 0
			&& info->n_start == NULL && !(info->ways = 0))
		return (special_insert(rooms, info, index, reads));
	else if (ft_strcmp(((char *)(*reads)->out), "##end") == 0
			&& info->n_end == NULL && (info->ways = 1))
		return (special_insert(rooms, info, index, reads));
	else if (ft_strncmp(((char *)(*reads)->out), "##", 2) == 0)
	{
		// info == ecrire error
		info->fourmies = -1;
		return (0);
	}
	if (info->n_end != NULL && ft_strcmp(((char *)(*reads)->out), "##end") == 0)
		return (0);
	if (info->n_start != NULL &&
			ft_strcmp(((char *)(*reads)->out), "##start") == 0)
		return (0);
	return (1);
}

static int		what_line(t_salle **rooms, t_out **index, char *line,
		int *truth)
{
	char	**splited;

	if (check_rformat(line) == 1 && *truth == 1)
	{
		splited = ft_strsplit(line, ' ');
		if (create_room(*rooms, splited[0], index) == -1)
		{
			free_all(splited, 0);
			return (0);
		}
		free_all(splited, 0);
		return (1);
	}
	else if (check_lformat(line, rooms, *truth) == 1)
	{
		if (*truth == 1)
			*truth = 2;
		return (1);
	}
	return (0);
}

void			check_insert(t_out **reads, t_out **index, t_salle **rooms,
		t_stack *info)
{
	char	*line;
	int		truth;

	truth = 0;
	line = NULL;
	while (free_reset(line) && get_next_line(0, &line) > 0)
	{
		out_add_tolist(reads, line, 0);
		if (line[0] == '#')
		{
			if ((!check_hash(info, index, rooms, reads)
						|| (!(info->fourmies) && line[1] == '#'))
					&& free_reset(line))
				break ;
		}
		else if (is_number(line, 0))
		{
			if (((info->fourmies != -1 || !is_number(line, 1))
				|| ((info->fourmies = ft_atoi_check(line)) <= 0)) && free_reset(line))
				break ;
			truth = 1;
		}
		else if (what_line(rooms, index, line, &truth) == 0 && free_reset(line))
			break ;
	}
}
