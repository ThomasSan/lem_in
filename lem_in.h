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
}					t_links;

typedef struct		s_rooms
{
	char			*name;
	int				is_start;
	int				is_end;
	int				ants;
	struct s_links	*links;
	struct s_rooms 	*next;
}					t_rooms;

int					get_next_line(int fd, char **line);
/*
**		parsing functions
*/
t_rooms				*parse_lines(t_rooms *head);
int					parse_ants(char *s);
int					parse_1_wd(char *s);
int					parse_3_wd(char *s);

#endif
