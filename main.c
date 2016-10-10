#include "lem_in.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

	tmp = closed;
	while (tmp)
	{
		printf("[DEBUG] closed: %s\n", tmp->name);
		tmp = tmp->next;
	}
	tmp = node->links;
	while (tmp)
	{
		if (is_closed(closed, tmp->name) == 0)
		{
			printf("[DEBUG] name: %s, cost %d\n", tmp->name, cost);
			node->weight = cost;
			closed = push_links(closed, tmp->name);
			set_weight(find_node(head, tmp->name), head, closed, cost + 1);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_rooms	*a_star_finding(t_rooms *head)
{
	t_rooms *end;
	// t_rooms *start;
	t_links *closed;

	closed = NULL;
	end = get_end_start(head, 1, 0);
	closed = push_links(closed, end->name);
	// start = get_end_start(head, 0, 1);
	set_weight(end, head, closed, 1);
	return (head);
}

int		main(void)
{
	t_shell	*shell;

	if (!(shell = (t_shell*)malloc(sizeof(t_shell))))
		return (0);
	shell->head = NULL;
	shell = parse_lines(shell);
	shell->head = a_star_finding(shell->head);
	show_list(shell);
	free(shell->head);
	free(shell);
	return (0);
}
