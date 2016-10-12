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

void	show_path(t_links *list)
{
	ft_putchar('\n');
	while (list)
	{
		printf("[PATH] -> %s", list->name);
		list = list->next;
	}
	printf("\n");
}

t_shell *shell_init(t_shell *shell, int ac, char **av)
{
	if (!(shell = (t_shell*)malloc(sizeof(t_shell))))
		return (0);
	shell->head = NULL;
	shell->color = 0;
	shell->ret = 0;
	shell->path = 0;
	shell->type = ANTS;
	while (--ac > 0)
	{
		if (ft_strcmp(av[ac], "-c") == 0)
			shell->color = 1;
		if (ft_strcmp(av[ac], "-p") == 0)
			shell->path = 1;
	}
	shell = parse_lines(shell);
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
