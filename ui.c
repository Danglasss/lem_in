/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 11:39:30 by nabboufe          #+#    #+#             */
/*   Updated: 2019/09/11 18:20:56 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		static_oui(char *str)
{
	static int		oui;

	while (str[oui] != '\0')
		oui++;
	return (oui);
}

int		main(void)
{
	int		oui;
	char	str[] = "mais?";

	oui = 0;
	static_oui("bmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais onbmais on");
	printf("%d\n", static_oui(str));
}


void		ft_bfs(t_salle *room, t_stack *find, t_pos *pos, t_pos *path)
{
	unsigned long		t_index;
	unsigned long		n_path;
	unsigned long		len_path;
	long long			prev_index;
	t_out				*tmp;
	int					count;

	n_path = len_pos(pos, 1);
	while (n_path-- && path->ways != NULL)
	// incrementer du chemin 1 au 2 etc...
	{
		count = 0;
		tmp = pos->ways->begin;
		// trouver les index des room
		ft_index(pos, &prev_index, &t_index);
		if (room[t_index].liens != NULL && room[t_index].liens->out != NULL)
			len_path = len_out(room[t_index].liens, 1);
		else
			continue ;
		while (pos->finish == 0 && len_path--)
		// incrementer par apport au liens
		{
			// Ajouter un nouveau chemin a pos
			if ((room[(unsigned long)room[t_index].liens->out].path == 0
				|| find->index_end == (unsigned long)room[t_index].liens->out) && count > 0 && (prev_index == -1
				|| (unsigned int)prev_index != (unsigned long)room[t_index].liens->out))
			{
				pos_add_tolist(&pos, NULL, 1);
				cpy_length(&pos->ways, tmp, find->lenght - 1);
			}
			// Ajouter un element a la fin du chemin
			if ((room[(unsigned long)room[t_index].liens->out].path == 0 || find->index_end == (unsigned long)room[t_index].liens->out) && (prev_index == -1 || (unsigned int)prev_index != (unsigned long)room[t_index].liens->out) && ++count)
				ft_add_room(room, pos, find, t_index);
			// copier le chemin finis dans path
			if (find->index_end == (unsigned long)room[t_index].liens->out)
				ft_copy(pos, find, path);
			// incrementation liens
			if (room[t_index].liens->next != NULL)
				room[t_index].liens = room[t_index].liens->next;
		}
		room[t_index].liens = room[t_index].liens->begin;
		find->lenght += 1;
		pos = pos->next;
	}
}