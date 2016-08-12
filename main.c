#include "lem_in.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int			main(void)
{
	t_rooms	*head;

	if (!(head = (t_rooms*)malloc(sizeof(t_rooms))))
		return (0);
	head = parse_lines(head);
	free(head);
	return (0);
}
