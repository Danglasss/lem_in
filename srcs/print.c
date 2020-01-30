/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danglass <danglass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:04:46 by dygouin          #+#    #+#             */
/*   Updated: 2020/01/30 15:07:10 by dygouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	print_list(t_out *p_list, t_salle *rooms)
{
	int		n_link;

	p_list = p_list->begin;
	while (p_list->out != NULL)
	{
		n_link = 0;
		ft_printf("Name of the room : %s\n", rooms[(int)p_list->out].salle);
		ft_printf("Links of that room : ");
		rooms[(int)p_list->out].liens = rooms[(int)p_list->out].liens->begin;
		while (rooms[(int)p_list->out].liens != NULL)
		{
			ft_printf("|Link (%d): '%s'| ",
				rooms[(int)p_list->out].liens->open,
				rooms[(unsigned long)rooms[(int)p_list->out].liens->out].salle);
			if (rooms[(int)p_list->out].liens->next != NULL)
				rooms[(int)p_list->out].liens =
					rooms[(int)p_list->out].liens->next;
			else
				break ;
			n_link++;
		}
		ft_printf("\n");
		if (p_list->next != NULL)
			p_list = p_list->next;
		else
			break ;
	}
}

void	ft_print_out(t_out *store, t_salle *room)
{
	while (store != NULL)
	{
		ft_printf("free ==  %d | ", room[(unsigned long)store->out].free);
		ft_printf("to print : '%s' | truth == %d\n",
		room[(unsigned long)store->out].salle, store->truth);
		store = store->next;
	}
}

void	ft_printread(t_out *read)
{
	while (read != NULL && read->out != NULL)
	{
		ft_printf("%s\n", (char *)read->out);
		read = read->next;
	}
	ft_printf("\n");
}

void	ft_print_till(t_out *out, unsigned long lenght, t_salle *room)
{
	int		n;

	n = 0;
	(void)room;
	while (out != NULL && out->out != NULL
			&& lenght >= (unsigned long)out->truth)
	{
		ft_printf("Node number %d == %d(%s) is %d\n", n,
				(unsigned long)out->out, 
				room[(unsigned long)out->out].salle,out->truth);
		if (out->next != NULL)
			out = out->next;
		else
			break ;
	}
	while (out != NULL && out->out != NULL)
	{
		ft_printf("Node number %d == %d(%s) out of the league (%d vs %d)",
		n, (unsigned long)out->out,
		room[(unsigned long)out->out].salle, lenght, out->truth);
		if (out->next != NULL)
			out = out->next;
		else
			break ;
	}
	ft_printf("\n\nEnd of ft_print_till\n\n");
}

/*
** A enlever :
**
*/

void	print(t_out *stack, t_salle *room)
{
	while (stack)
	{
		ft_printf("%s\n", room[stack->index].salle);
		stack = stack->next;
	}
	ft_printf("\n");
}

void	print_lien(t_out *stack, t_salle *room)
{
	ft_printf("\nVoici les liens\n");
	while (stack)
	{
		ft_printf("%s | state : %d\n", room[(unsigned long)stack->out].salle, stack->open);
		if (stack->next == NULL)
			break ;
		stack = stack->next;
	}
	stack = stack->begin;
	ft_printf("\n");
}

void	print_salle(t_out *stack, t_salle *room)
{
	ft_printf("\nVoici les salles\n");
	while (stack)
	{
		ft_printf("%s\n", room[stack->index].salle);
		if (stack->next == NULL)
			break ;
		stack = stack->next;
	}
	stack = stack->begin;
	ft_printf("\n");
}

