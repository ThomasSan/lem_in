/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 17:58:48 by tsanzey           #+#    #+#             */
/*   Updated: 2016/10/23 17:58:49 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define END 1
# define START 2
# define ERROR -1
# define ANTS 100
# define ROOMS 101
# define PIPES 102
# define OUT 300
# define IN 303
# include "libft/libft.h"
# include <stdlib.h>

typedef struct		s_ants
{
	int				ant;
	int				status;
	struct s_links	*room;
	struct s_ants	*next;
}					t_ants;

typedef struct		s_links
{
	char			*name;
	struct s_links	*next;
}					t_links;

typedef struct		s_rooms
{
	char			*name;
	int				is_start;
	int				is_end;
	int				weight;
	struct s_links	*links;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_shell
{
	int				ants;
	int				color;
	int				path;
	int				type;
	int				ret;
	struct s_rooms	*head;
}					t_shell;

int					get_next_line(int fd, char **line);
/*
**		parsing functions
*/
t_shell				*parse_lines(t_shell *shell);
int					parse_ants(char *s);
int					parse_1_wd(char *s);
int					parse_3_wd(char *s);
int					parse_pipes(char *s, t_rooms *head);
/*
**		listwise functions
*/
t_rooms				*push_back(t_rooms *head, char *name, int start, int end);
t_rooms				*fill_room(t_rooms *head, char *str, int room);
int					matching_mames(t_rooms *head, char *s1, char *s2);
void				fill_pipes(t_rooms *head, char *s);
t_links				*push_links(t_links *links, char *s);
void				free_links(t_links *links);
/*
**		Ayray functions
*/
void				free_array(char **arr);
/*
**		Errors & free functions
*/
int					my_error(int x, t_shell *shell);
void				free_shell_links(t_shell *shell);
void				free_path(t_links **path);
void				free_links(t_links *links);
/*
**		PathFinding functions
*/
t_rooms				*get_end_start(t_rooms *head, int end, int start);
t_rooms				*a_star_finding(t_rooms *head);
void				print_path(t_shell *shell, t_links *path);
void				get_path(t_rooms *head, t_rooms *start, t_links *path);

#endif
