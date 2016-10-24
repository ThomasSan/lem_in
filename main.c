/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 17:55:03 by tsanzey           #+#    #+#             */
/*   Updated: 2016/10/23 17:55:05 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_rooms	*push_back(t_rooms *head, char *name, int start, int end)
{
	t_rooms *new;
	t_rooms *tmp;

	if (!(new = (t_rooms*)malloc(sizeof(t_rooms))))
		return (NULL);
	new->name = ft_strdup(name);
	new->is_start = start;
	new->is_end = end;
	new->weight = 0;
	new->links = NULL;
	new->next = NULL;
	if (!head)
		head = new;
	else
	{
		tmp = head;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->name, name) == 0)
				my_error(3, NULL);
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	return (head);
}

void	show_list(t_shell *shell)
{
	ft_putstr("ants : ");
	ft_putnbr(shell->ants);
	while (shell->head)
	{
		if (shell->head->is_start)
			ft_putstr("start : ");
		if (shell->head->is_end)
			ft_putstr("end : ");
		ft_putstr("name");
		ft_putendl(shell->head->name);
		while (shell->head->links)
		{
			ft_putstr("\tlinks ");
			ft_putendl(shell->head->links->name);
			shell->head->links = shell->head->links->next;
		}
		shell->head = shell->head->next;
	}
}

void	show_path(t_links *list)
{
	ft_putchar('\n');
	while (list)
	{
		ft_putstr("[PATH] -> ");
		ft_putstr(list->name);
		list = list->next;
	}
	ft_putchar('\n');
}

t_shell	*shell_init(t_shell *shell, int ac, char **av)
{
	if (!(shell = (t_shell*)malloc(sizeof(t_shell))))
		return (0);
	shell->head = NULL;
	shell->color = 0;
	shell->ret = 0;
	shell->path = 0;
	shell->start = 0;
	shell->end = 0;
	shell->type = ANTS;
	while (--ac > 0)
	{
		if (ft_strcmp(av[ac], "-c") == 0)
			shell->color = 1;
		if (ft_strcmp(av[ac], "-p") == 0)
			shell->path = 1;
	}
	shell = parse_lines(shell, NULL);
	return (shell);
}

int		main(int ac, char **av)
{
	t_shell	*shell;
	t_links	*path;
	t_rooms	*start;

	shell = NULL;
	shell = shell_init(shell, ac, av);
	path = NULL;
	if (!get_end_start(shell->head, 0, 1) || !get_end_start(shell->head, 1, 0))
		return (my_error(2, shell));
	shell->head = a_star_finding(shell->head);
	start = get_end_start(shell->head, 0, 1);
	path = push_links(path, start->name);
	get_path(shell->head, start, path);
	if (shell->path)
		show_path(path);
	free_path(&path);
	print_path(shell, path);
	free_shell_links(shell);
	free_links(path);
	return (0);
}
