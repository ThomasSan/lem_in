/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 17:50:55 by tsanzey           #+#    #+#             */
/*   Updated: 2016/10/23 17:50:56 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_ants(t_ants *list, int turn, int color)
{
	while (list && list->ant <= turn)
	{
		if (list->status == IN)
		{
			if (color)
				ft_putstr("\x1B[35m");
			ft_putchar('L');
			ft_putnbr(list->ant);
			ft_putstr("\x1B[0m");
			ft_putchar('-');
			if (color)
				ft_putstr("\x1B[32m");
			ft_putstr(list->room->name);
			ft_putstr("\x1B[0m");
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
	ft_putchar('\n');
	while (i++ < shell->ants)
		ant_list = push_ants(ant_list, i, path);
	i = 1;
	while (ants_status(ant_list))
	{
		print_ants(ant_list, i, shell->color);
		i++;
	}
	free_ant_list(ant_list);
}
