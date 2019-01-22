/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:09:34 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/18 14:09:36 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "./libft/libft.h"

# define START 1
# define END 2
# define NORMAL 0

typedef struct	s_room
{
	char *name;
	int x;
	int y;
	int s_e;
}				t_room;

typedef struct	s_link
{
	int rm1;
	int rm2;
}				t_link;

typedef struct	s_inf
{
	int ants;
	int rooms;
	int links;
	t_room	*room;
	t_link	*link;
}				t_inf;

typedef struct		s_fl
{
	char			*line;
	struct s_fl		*next;
}					t_fl;

typedef	struct		s_node
{
	int value;
	int *edges;
	int searched;
	int parent;
}					t_node;

typedef struct 		s_graph
{
	t_node	*nodes;
	int		*gr;
	int		start;
	int		end;
}					t_graph;

void		read_map(char **av, t_inf *info);
void		exit_l(char *str);
size_t		ft_strlen_chr(const char *s, int c);
void		parsing(t_fl *file, t_inf *info);
void		make_graph(t_inf *info);
void		bfs(t_graph *graph, t_inf *info);

#endif