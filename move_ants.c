/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 16:53:21 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/31 16:53:22 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

int		*lenght_ways(t_ways *res, int numb)
{
	t_way		*start;
	int			*len;
	int			i;

	i = 0;
	start = NULL;
	len = (int*)malloc(sizeof(int) * numb);
	while (res)
	{
		start = res->ways;
		len[i] = 0;
		while (start)
		{
			start = start->after;
			len[i]++;
		}
		len[i] -= 2;
		i++;
		res = res->next;
	}
	len[i] = 0;
	free(start);
	return (len);
}

void	run(t_move *transp, t_inf *info, t_way **start, t_graph *graph)
{
	t_way	**buf;

	buf = fill_buf(graph, start);
	while (transp[info->ants - 1].room != graph->end)
	{
		if (graph->ants == info->ants)
			new_line(&graph->ants, &graph->lines);
		graph->d = transp[graph->ants].way;
		start[graph->d] = buf[graph->d];
		first_action(transp, &start[graph->d], graph, &graph->ants);
		if ((start[graph->d]->ant != -1 && start[graph->d]->ant !=\
		transp[graph->ants].ant && start[graph->d]->content != graph->end))
			new_line(&graph->ants, &graph->lines);
		graph->d = transp[graph->ants].way;
		start[graph->d] = buf[graph->d];
		first_action(transp, &start[graph->d], graph, &graph->ants);
		if (start[graph->d]->ant == -1 && start[graph->d]->ant != transp[graph->ants].ant)
			print(&transp[graph->ants], start[graph->d], info, &graph->ants);
		else if (start[graph->d]->ant == transp[graph->ants].ant)
		{
			start[graph->d]->ant = -1;
			start[graph->d] = start[graph->d]->after;
			print(&transp[graph->ants], start[graph->d], info, &graph->ants);
		}
	}
	new_line(&graph->ants, &graph->lines);
	free(buf);
}

void	choose_ways(t_inf *info, t_graph *graph, t_way **start, t_move *transp)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	k = 0;
	while (i < info->ants)
	{
		j = -1;
		while (++j < graph->numb_ways)
		{
			if (graph->ants > how_much(graph->len_ways, j))
			{
				if_start((start), graph, j);
				fill_transp(&transp[k], (start)[j]->content, &i, j);
				graph->ants--;
				k++;
			}
		}
		if (i == info->ants - 1)
		{
			if_start((start), graph, 0);
			fill_transp(&transp[k], (start)[0]->content, &i, 0);
		}
	}
}

void	move_ants(t_ways *res, t_inf *info, t_graph *graph)
{
	t_way		**start;
	t_way		**begin;
	t_move		*transp;

	transp = (t_move*)malloc(sizeof(t_way) * info->ants);
	start = (t_way**)malloc(sizeof(t_way*) * graph->numb_ways);
	begin = (t_way**)malloc(sizeof(t_way*) * graph->numb_ways);
	graph->len_ways = lenght_ways(res, graph->numb_ways);
	graph->ants = info->ants;
	start_begin(graph, start, begin, res);
	choose_ways(info, graph, start, transp);
	run(transp, info, begin, graph);
	free(transp);
	free(begin);
	free(start);
	if (info->lines == 1)
	{
		ft_printf("\033[01;33m");
		ft_printf("\nlines = %d\n", graph->lines);
		ft_printf("\033[0m");
	}
}
