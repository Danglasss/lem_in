void	path(t_salle *room, t_stack *find, unsigned long end)
{
	unsigned long index;
	
	index = end;
	while (index != find->index_start)
	{
		ft_printf("\n\nsalle : %s \n", room[index].salle);
		room[index].liens = room[index].liens->begin;
		while (room[index].liens)
		{
			ft_printf("liens : %s || open : %d\n", room[(unsigned long)room[index].liens->out].salle, room[index].liens->open);
			room[index].liens = room[index].liens->next;
		}
		index = room[index].salle_prev;
	}
	ft_printf("\n\nsalle : %s \n", room[index].salle);
	room[index].liens = room[index].liens->begin;
	while (room[index].liens)
	{
		ft_printf("liens : %s || open : %d\n", room[(unsigned long)room[index].liens->out].salle, room[index].liens->open);
		room[index].liens = room[index].liens->next;
	}
	
}
