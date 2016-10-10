#ifndef LEM_IN_H
# define LEM_IN_H

# define END 1
# define START 2
# define ERROR -1
# define ANTS 100
# define ROOMS 101
# define PIPES 102
#include "libft/libft.h"
#include <stdlib.h>

typedef struct 		s_links
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
	struct s_rooms 	*next;
}					t_rooms;


typedef struct 		s_shell
{
	int				ants;
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
t_rooms		*push_back(t_rooms *head, char *name, int start, int end);
t_rooms 	*fill_room(t_rooms *head, char *str, int room);
int			matching_mames(t_rooms *head, char *s1, char *s2);
void		fill_pipes(t_rooms *head, char *s);
t_links		*push_links(t_links *links, char *s);
/*
**		Ayray functions
*/
void	free_array(char **arr);


#endif
