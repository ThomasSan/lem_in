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

int		ft_checkline(char *s, int type, t_rooms *head)
{
	int wd;

	if (s[0] == '#')
		return (parse_1_wd(s));
	wd = word_nb(s);
	if (wd > 3 || wd == 2)
		return (ERROR);
	if (wd == 1 && type == ANTS)
		return (parse_ants(s));
	if (wd == 3)
	{
		if (type != ROOMS)
			return (ERROR);
		return (parse_3_wd(s));
	}
	if (wd == 1)
		return (parse_pipes(s, head));
	return (0);
}

t_shell	*parse_lines(t_shell *shell)
{
	char	*buff;
	int		ret;
	int		type;

	buff = NULL;
	type = ANTS;
	ret = 0;
	while (get_next_line(0, &buff))
	{
		if (ret == START || ret == END)
		{
			shell->head = fill_room(shell->head, buff, ret);
			ret = 0;
			continue;
		}
		ret = ft_checkline(buff, type, shell->head);
		// printf("buff : %s, ret : %d\n", buff, ret);
		if (ret == ERROR)
			break ;
		else if (ret == ANTS)
		{
			shell->ants = ft_atoi(buff);
			type = ROOMS;
		}
		else if (ret == ROOMS)
			shell->head = fill_room(shell->head, buff, ret);
		else if (ret == PIPES)
			fill_pipes(shell->head, buff);
		free(buff);
	}
	return (shell);
}