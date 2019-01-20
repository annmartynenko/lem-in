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

#define START 1

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
	struct s_list	*next;
}					t_fl;

void	read_map(char **av, t_inf *info);
void	exit_l(int c);
size_t ft_strlen_chr(const char *str, int c);

#endif