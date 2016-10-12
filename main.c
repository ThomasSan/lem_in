#include "lem_in.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		my_error(int x)
{
	ft_putendl("\nERROR");
	printf("(%d)\n", x);
	exit(-1);
	return (-1);
}

void	show_list(t_shell *shell)
{
	printf("ants : %d\n", shell->ants);
	while(shell->head)
	{
		if (shell->head->is_start)
			printf("start : ");
		if (shell->head->is_end)
			printf("end : ");
		printf("name %s, cost %d\n", shell->head->name, shell->head->weight);
		while (shell->head->links)
		{
			printf("\tlinks %s\n", shell->head->links->name);
			shell->head->links = shell->head->links->next;
		}
		shell->head = shell->head->next;
	}
}

void	show_path(t_links *list)
{
	while (list)
	{
		printf("[PATH] -> %s", list->name);
		list = list->next;
	}
	printf("\n");
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
		if (is_closed(closed, tmp->name) == 0 && (current_node->weight == 0 || current_node->weight > cost))
		{
			// printf("[DEBUG] node: %s name: %s, cost %d\n", node->name, current_node->name, cost);
			current_node->weight = cost;
		}
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
	t_rooms	*current_node;

	cost = -1;
	tmp = start->links;
	save = NULL;
	while (tmp)
	{
		current_node = find_node(head, tmp->name);
		if ((current_node->weight <= start->weight) && is_closed(path, tmp->name) == 0)
		{
			save = tmp;
			cost = current_node->weight < cost;
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

int		main(void)
{
	t_shell	*shell;
	t_links	*path;
	t_links	*tmp;
	t_rooms	*start;

	if (!(shell = (t_shell*)malloc(sizeof(t_shell))))
		return (0);
	shell->head = NULL;
	path = NULL;
	shell = parse_lines(shell);
	if (!get_end_start(shell->head, 0, 1) || !get_end_start(shell->head, 1, 0))
		return (my_error(2));
	shell->head = a_star_finding(shell->head);
	start = get_end_start(shell->head, 0, 1);
	path = push_links(path, start->name);
	get_path(shell->head, start, path);
	// show_path(path);
	tmp = path;
	path = path->next;
	free(tmp->name);
	free(tmp);
	print_path(shell, path);
	free_shell_links(shell);
	free_links(path);
	return (0);
}
