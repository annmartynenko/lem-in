/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:43:29 by amartyne          #+#    #+#             */
/*   Updated: 2019/02/24 16:43:30 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

void	print_ways(t_ways *res, t_inf *info)
{
	t_way *tmp;

	ft_printf("\nWAYS\n");
	while (res)
	{
		tmp = res->ways;
		while (tmp->after)
		{
			ft_printf("%s-> ", info->room[tmp->content].name);
			tmp = tmp->after;
		}
		ft_printf("%s\n", info->room[tmp->content].name);
		res = res->next;
	}
	ft_printf("\n");
}

void	clean_res(t_ways *res)
{
	t_way		*tmp;
	t_ways		*tmp123;
	void		*tmp321;

	tmp = NULL;
	tmp123 = NULL;
	tmp321 = NULL;
	while (res)
	{
		tmp = res->ways;
		while (tmp)
		{
			tmp321 = tmp->after;
			free(tmp);
			tmp = tmp321;
		}
		tmp123 = res->next;
		free(res);
		res = tmp123;
	}
}

void	clean_start(t_way *start)
{
	t_way *tmp;

	while (start)
	{
		tmp = start->after;
		free(start);
		start = tmp;
	}
}
