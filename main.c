#include "lem_in.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_rooms		*push_back(t_rooms *head, char *name, int start, int end)
{
	(void)name;
	(void)start;
	(void)end;
	return (head);
}

int			main(void)
{
	char	*buff;
	t_rooms	*head;
	
	buff = NULL;
	head = NULL;
	if (!(head = (t_rooms*)malloc(sizeof(t_rooms))))
		return (0);
	while (get_next_line(0, &buff))
	{
		printf("%s\n", buff);
		// if (ft_checkline());
	}
	return (0);
}
