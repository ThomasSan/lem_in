#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct 		s_links
{
	char			*name;
}					t_links;

typedef struct		s_rooms
{
	char			*name;
	int				is_start;
	int				is_end;
	struct s_links	*links;
	struct s_rooms 	*next;
}					t_rooms;

int		get_next_line(int fd, char **line);
#endif
