#include "lem_in.h"
#include <stdio.h>

int		word_nb(char *s)
{
	int i;
	int wd;

	i = 0;
	wd = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		wd++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (wd);
}

int		ft_checkline(char *s, int type)
{
	int wd;

	if (s[0] == '#' && s[1] && s[1] != '#')
		return (3);
	wd = word_nb(s);
	if (wd > 3 || wd == 2)
		return (ERROR);
	if (wd == 1 && type == ANTS)
		return (parse_ants(s));
	if (wd == 1)
		return (parse_1_wd(s));
	if (wd == 3)
	{
		if (type != ROOMS)
			return (-1);
		return (parse_3_wd(s));
	}
	return (0);
}

t_rooms	*parse_lines(t_rooms *head)
{
	char	*buff;
	int		ret;
	int		type;

	buff = NULL;
	type = ANTS;
	while (get_next_line(0, &buff))
	{
		ret = ft_checkline(buff, type);
		printf("buff : %s, ret %d\n", buff, ret);
		if (ret == ERROR)
			break ;
		else if (ret == ANTS)
		{
			head->ants = ft_atoi(buff);
			type = ROOMS;
		}
		// else if (ret = END)
		// else if (ret = START)
		// else
		free(buff);
	}
	return (head);
}