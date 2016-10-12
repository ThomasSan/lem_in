#include "lem_in.h"

t_ants	*push_ants(t_ants *ant, int i, t_links *room)
{
	t_ants *new;
	t_ants *tmp;

	if (!(new = (t_ants*)malloc(sizeof(t_ants))))
		return (NULL);
	new->ant = i;
	new->status = IN;
	new->room = room;
	new->next = NULL;
	if (!ant)
		ant = new;
	else
	{
		tmp = ant;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (ant);
}

int		ants_status(t_ants *list)
{
	while (list)
	{
		if (list->status != OUT)
			return (1);
		list = list->next;
	}
	return (0);
}

void	print_ants(t_ants *list, int turn)
{
	while (list && list->ant <= turn)
	{
		if (list->status == IN)
		{
			ft_putchar('L');
			ft_putnbr(list->ant);
			ft_putchar('-');
			ft_putstr(list->room->name);
			ft_putchar(' ');
			list->room = list->room->next;
			if (!list->room)
				list->status = OUT;
		}
		list = list->next;
	}
	ft_putchar('\n');
}

void	free_ant_list(t_ants *list)
{
	t_ants *tmp;
	while (list)
	{
		tmp = list;	
		list = list->next;
		free(tmp->room);
		free(tmp);
	}
}

void	print_path(t_shell *shell, t_links *path)
{
	t_ants	*ant_list;
	int		i;

	i = 0;
	ant_list = NULL;
	while (i++ < shell->ants)
		ant_list = push_ants(ant_list, i, path);
	i = 1;
	while (ants_status(ant_list))
	{
		print_ants(ant_list, i);
		i++;
	}
	free_ant_list(ant_list);
}