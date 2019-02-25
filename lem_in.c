/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:08:00 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/18 14:08:02 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

void	flags(int ac, char **av, t_inf *info)
{
	if (!ft_strcmp("-help", av[1]))
	{
		ft_printf("-ways - show all founded ways\n");
		ft_printf("-lines - show number of output lines\n");
		ft_printf("-help - info about all flags\n");
		exit(0);
	}
	if ((ac > 1 && !ft_strcmp("-lines", av[1])) || (ac > 2 && \
	!ft_strcmp("-lines", av[2])))
	{
		info->lines = 1;
		ft_printf("lines\n");
	}
	if ((ac > 1 && !ft_strcmp("-ways", av[1])) || (ac > 2 && \
	!ft_strcmp("-ways", av[2])))
	{
		info->ways = 1;
		ft_printf("ways\n");
	}
}

int		main(int ac, char **av)
{
	t_inf	info;

	info.ants = 0;
	info.rooms = 0;
	info.room = NULL;
	info.links = 0;
	info.ways = 0;
	info.lines = 0;
	info.s_e = 0;
	info.link = NULL;
	if (ac != 0)
//		flags(ac, av, &info);
	{
		read_map(&info, av);
		make_graph(&info);
	}
//	system("leaks lem-in");
	return (0);
}
