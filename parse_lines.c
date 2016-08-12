#include <stdio.h>
#include "lem_in.h"

int		parse_ants(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		i++;
	}
	return (ANTS);
}

int		parse_1_wd(char *s)
{
	// int i;

	// i = 0;
	if (ft_strcmp("##start", s) == 0)
		return (START);
	if (ft_strcmp("##end", s) == 0)
		return (END);
	// verifier les tubes
	return (0);
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

	i = 0;
	printf("s : %s\n", s);
	arr = ft_split(s);
	// printf("arr0 %s arr1 %s arr2 %s \n", arr[0], arr[1], arr[2]);
	if (arr[0][0] == 'L')
		return (ERROR);
	while (arr[1][i])
	{
		if (!ft_isdigit(arr[1][i]))
			return (ERROR);
		i++;
	}
	i = 0;
	while (arr[2][i])
	{
		if (!ft_isdigit(arr[2][i]))
			return (ERROR);
		i++;
	}
	free_array(arr);
	free(arr);
	return (0);
}