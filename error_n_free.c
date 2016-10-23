/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_n_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 17:56:59 by tsanzey           #+#    #+#             */
/*   Updated: 2016/10/23 17:57:00 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	free_links(t_links *links)
{
	t_links *tmp;

	while (links)
	{
		tmp = links;
		links = links->next;
		free(tmp->name);
		free(tmp);
	}
}

t_rooms	*get_end_start(t_rooms *head, int end, int start)
{
	t_rooms *tmp;

	tmp = head;
	while (tmp)
	{
		if (end && tmp->is_end)
			return (tmp);
		if (start && tmp->is_start)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_shell_links(t_shell *shell)
{
	t_rooms	*tmp_room;
	t_links	*tmp_links;

	tmp_room = shell->head;
	while (shell->head)
	{
		while (shell->head->links)
		{
			tmp_links = shell->head->links;
			shell->head->links = shell->head->links->next;
			free(tmp_links->name);
			free(tmp_links);
		}
		tmp_room = shell->head;
		shell->head = shell->head->next;
		free(tmp_room->name);
		free(tmp_room);
	}
	free(shell->head);
	free(shell);
}

void	free_path(t_links **path)
{
	t_links	*tmp;

	tmp = *path;
	*path = tmp->next;
	free(tmp->name);
	free(tmp);
}

int		my_error(int x, t_shell *shell)
{
	(void)x;
	ft_putendl("\nERROR");
	ft_putchar('\n');
	if (shell)
		free_shell_links(shell);
	exit(-1);
	return (-1);
}
