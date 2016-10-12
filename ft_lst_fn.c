#include "lem_in.h"
#include <stdio.h>

t_rooms		*push_back(t_rooms *head, char *name, int start, int end)
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
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (head);
}

t_rooms 	*fill_room(t_rooms *head, char *str, int room)
{
	char **arr;

	arr = ft_split(str);
	if (room == START)
		head = push_back(head, arr[0], 1, 0);
	else if (room == END)
		head = push_back(head, arr[0], 0, 1);
	else 
		head = push_back(head, arr[0], 0, 0);
	free_array(arr);
	free(arr);
	return (head);
}

int			matching_mames(t_rooms *head, char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (head)
	{
		if (ft_strcmp(head->name, s1) == 0)
			i++;
		if (ft_strcmp(head->name, s2) == 0)
			j++;
		head = head->next;
	}
	if (i && j)
		return (1);
	return (0);
}

int		get_pipes(char *s, t_rooms *head, char **s1, char **s2)
{
	int		i;

	i = 0;
	while (s[i]){
		if (s[i] == '-')
		{
			*s1 = ft_strsub(s, 0, i);
			*s2 = ft_strsub(s, i + 1, ft_strlen(s));
			if (matching_mames(head, *s1, *s2))
				return (1);
			free(*s1);
			free(*s2);
			*s1 = NULL;
			*s2 = NULL;
		}
		i++;
	}
	return (1);
}

t_links	*push_links(t_links *links, char *s)
{
	t_links *new;
	t_links *tmp;

	if (!(new = (t_links*)malloc(sizeof(t_links))))
		return (NULL);
	new->name = ft_strdup(s);
	new->next = NULL;
	if (!links)
		links = new;
	else
	{
		tmp = links;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (links);
}

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

void	fill_pipes(t_rooms *head, char *s)
{
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	get_pipes(s, head, &s1, &s2);
	while (head)
	{
		if (ft_strcmp(head->name, s1) == 0)
			head->links = push_links(head->links, s2);
		if (ft_strcmp(head->name, s2) == 0)
			head->links = push_links(head->links, s1);
		head = head->next;
	}
	free(s1);
	free(s2);
}