#include <stdio.h>
#include "lem_in.h"

int		parse_ants(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (ERROR);
		i++;
	}
	return (ANTS);
}

int		parse_1_wd(char *s)
{
	if (ft_strcmp("##start", s) == 0)
		return (START);
	if (ft_strcmp("##end", s) == 0)
		return (END);
	return (3);
}

void	free_array(char **arr)
{
	int i;

	i = 0;
	while (i < 3)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
}

int		parse_3_wd(char *s)
{
	char	**arr;
	int		i;

	arr = ft_split(s);
	if (arr[0][0] == 'L')
		return (ERROR);
	i = arr[1][0] == '-' ? 1 : 0;
	while (arr[1][i])
	{
		if (!ft_isdigit(arr[1][i]))
			return (ERROR);
		i++;
	}
	i = arr[2][0] == '-' ? 1 : 0;
	while (arr[2][i])
	{
		if (!ft_isdigit(arr[2][i]))
			return (ERROR);
		i++;
	}
	free_array(arr);
	free(arr);
	return (ROOMS);
}

int		parse_pipes(char *s, t_rooms *head)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	while (s[i]){
		if (s[i] == '-')
		{
			tmp1 = ft_strsub(s, 0, i);
			tmp2 = ft_strsub(s, i + 1, ft_strlen(s));
			if (matching_mames(head, tmp1, tmp2))
			{
				free(tmp1);
				free(tmp2);
				return (PIPES);
			}
			free(tmp1);
			free(tmp2);
		}
		i++;
	}
	return (ERROR);
}