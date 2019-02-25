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
	char		*name;
	int			x;
	int			y;
	int			s_e;
}				t_room;

typedef struct	s_link
{
	int			rm1;
	int			rm2;
}				t_link;

typedef struct	s_inf
{
	int			ants;
	int			rooms;
	int			links;
	int			ways;
	int 		s_e;
	int			lines;
	t_room		*room;
	t_link		*link;
}				t_inf;

typedef struct		s_fl
{
	char			*line;
	struct s_fl		*next;
}					t_fl;

typedef	struct		s_node
{
	int				value;
	int				*edges;
	int				n_edg;
	int				searched;
	int				note;
}					t_node;

typedef struct 		s_graph
{
	t_node			*nodes;
	int				start;
	int				end;
	int				numb_ways;
	int 			current;
	int 			neighbor;
	int 			lines;
	int 			ants;
	int 			d;
	int				*len_ways;
}					t_graph;

typedef struct		s_way
{
	int				content;
	int				ant;
	struct s_way	*after;
}					t_way;

typedef struct		s_ways
{
	t_way			*ways;
	struct s_ways	*next;
}					t_ways;

typedef struct		s_move
{
	int				ant;
	int				room;
	int				way;
}					t_move;

void				read_map(t_inf *info, char **av);
void				exit_l(char *str);
size_t				ft_strlen_chr(const char *s, int c);
void				parsing(t_fl *file, t_inf *info);
void				make_graph(t_inf *info);
void				bfs(t_graph *graph, t_inf *info);
void   				move_ants(t_ways *res, t_inf *info, t_graph *graph);
int 				how_much(int *len, int j);
void				print(t_move *transp, t_way *start, t_inf *info, int *k);
void				first_action(t_move *transp, t_way **start, t_graph *graph, int *k);
t_way				**fill_buf(t_graph *graph, t_way **start);
void				new_line(int *k, int *lines);
void				fill_transp(t_move *transp, int room, int *i, int j);
void				start_begin(t_graph *graph, t_way **start, t_way **begin, t_ways *res);
void				if_start(t_way **start, t_graph *graph, int j);
void				print_ways(t_ways *res, t_inf *info);
void				clean_res(t_ways *res);
void				clean_start(t_way *start);
int					check_searched(t_way *start, t_graph *graph);
void				move_and_check(t_ways *queue, t_graph *graph);
t_ways				*create_queue(t_graph *graph);
void				conditions(t_graph *graph, t_inf *info, t_ways *res);
void				fill_node(t_graph **graph, int i, int *k, int paste);
void				find_se(t_graph **graph, t_inf *info);
int					count_edges(t_inf *info, int i);
void				links(t_graph *graph, t_inf *info, int i);
void				clean_buf(t_fl **file, t_fl **buf);

#endif