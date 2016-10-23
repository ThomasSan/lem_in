/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 17:51:25 by tsanzey           #+#    #+#             */
/*   Updated: 2016/10/23 17:51:26 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	buff = NULL;
	while (get_next_line(0, &buff))
	{
		ft_putendl(buff);
		if ((shell->ret == START || shell->ret == END) && shell->type != ANTS)
		{
			if (ft_checkline(buff, shell->type, shell->head) == 3)
			{
				free(buff);
				continue ;
			}
			shell->head = fill_room(shell->head, buff, shell->ret);
			shell->ret = 0;
			free(buff);
			continue;
		}
		shell->ret = ft_checkline(buff, shell->type, shell->head);
		if (shell->ret == ERROR)
			break ;
		else if (shell->ret == ANTS)
		{
			shell->ants = ft_atoi(buff);
			shell->type = ROOMS;
		}
		else if (shell->ret == ROOMS)
			shell->head = fill_room(shell->head, buff, shell->ret);
		else if (shell->ret == PIPES)
		{
			fill_pipes(shell->head, buff);
			shell->type = PIPES;
		}
		free(buff);
	}
	return (shell);
}
