/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 17:40:57 by tsanzey           #+#    #+#             */
/*   Updated: 2016/10/23 17:40:59 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*find_node(t_rooms *head, char *name)
{
	t_rooms *tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int		is_closed(t_links *list, char *s)
{
	while (list)
	{
		if (ft_strcmp(list->name, s) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

int		set_weight(t_rooms *node, t_rooms *head, t_links *closed, int cost)
{
	t_links *tmp;
	t_rooms	*current_node;

	tmp = node->links;
	while (tmp)
	{
		current_node = find_node(head, tmp->name);
		if (is_closed(closed, tmp->name) == 0 && (current_node->weight == 0 ||
current_node->weight > cost))
			current_node->weight = cost;
		tmp = tmp->next;
	}
	tmp = node->links;
	while (tmp)
	{
		current_node = find_node(head, tmp->name);
		if (is_closed(closed, tmp->name) == 0)
		{
			closed = push_links(closed, tmp->name);
			set_weight(current_node, head, closed, cost + 1);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_rooms	*a_star_finding(t_rooms *head)
{
	t_rooms *end;
	t_links *closed;

	closed = NULL;
	end = get_end_start(head, 1, 0);
	closed = push_links(closed, end->name);
	set_weight(end, head, closed, 1);
	free_links(closed);
	return (head);
}

void	get_path(t_rooms *head, t_rooms *start, t_links *path)
{
	int		cost;
	t_links *tmp;
	t_links *save;
	t_rooms	*curr;

	cost = -1;
	tmp = start->links;
	save = NULL;
	while (tmp)
	{
		curr = find_node(head, tmp->name);
		if ((curr->weight <= start->weight) && is_closed(path, tmp->name) == 0)
		{
			save = tmp;
			cost = curr->weight < cost;
		}
		tmp = tmp->next;
	}
	if (start == get_end_start(head, 1, 0))
		return ;
	if (start != get_end_start(head, 1, 0))
	{
		path = push_links(path, save->name);
		get_path(head, find_node(head, save->name), path);
	}
}
