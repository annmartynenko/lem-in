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

int 	*lenght_ways(t_ways *res, int numb)
{
	t_way		*start;
	int         *len;
	int i;

	i = 0;
	start = NULL;
	len = (int*)malloc(sizeof(int) * numb);
	printf("NUMB %d\n", numb);
	while (res)
	{
		start = res->ways;
		len[i] = 0;
		while (start)
		{
			printf("start %d \n", start->content);
			start = start->after;
			len[i]++;
		}
		len[i] -= 2;
		printf(" i %d, len[%d]\n", len[i], i);
		i++;
		res = res->next;
	}
	len[i] = 0;
	free(start);
	return (len);
}

void	run(t_moving *transp, t_inf *info, t_way **start, t_graph *graph)
{
	int k;
	int d;
	t_way **buf;

	d = 0;
	k = 0;
	buf = (t_way**)malloc(sizeof(t_way*) * graph->numb_ways);
	fill_buf(graph, start, buf);
	while (transp[info->ants - 1].room != graph->end)
	{
		if (k == info->ants)
			k = 0;
		d = transp[k].way;
		start[d] = buf[d];
		first_action(transp, &start[d], graph, &k);
//		printf("     { start %d, transp %d, d %d, k %d }   \n", start[d]->ant, transp[k].ant, d, k);
		if (k == info->ants || (start[d]->ant != -1 && start[d]->ant != transp[k].ant) || k == 0)
			new_line(&k);
		d = transp[k].way;
		start[d] = buf[d];
		first_action(transp, &start[d], graph, &k);
		if (start[d]->ant == -1)
			print(&transp[k], start[d], info, &k);
		else if (start[d]->ant == transp[k].ant)
		{
			start[d]->ant = -1;
			start[d] = start[d]->after;
			print(&transp[k], start[d], info, &k);
		}
	}
	free(buf);
}

void	choose_ways(t_inf *info, t_graph *graph, t_way **start, t_moving *transp)
{
	int 		i;
	int 		j;
	int 		ants;
	int 		k;

	i = 0;
	k = 0;
	ants = info->ants;
	while (i < info->ants)
	{
		j = 0;
		while (j < graph->numb_ways)
		{
			if (ants > how_much(graph->len_ways, j))
			{
				if_start((start), graph, j);
				fill_transp(&transp[k], (start)[j]->content, i, j);
				printf("ant %d, way %d \n", transp[k].ant, transp[k].way);
				ants--;
				i++;
				k++;
			}
			else if (i == info->ants - 1)
				break;
			j++;
		}
		if (i == info->ants - 1)
		{
			if_start((start), graph, 0);
			fill_transp(&transp[k], (start)[0]->content, i, 0);
			break ;
		}
	}
}

void    move_ants(t_ways *res, t_inf *info, t_graph *graph)
{
	t_way		**start;
	t_way		**begin;
	t_moving	*transp;


	transp = (t_moving*)malloc(sizeof(t_way) * info->ants);
	start = (t_way**)malloc(sizeof(t_way*) * graph->numb_ways);
	begin = (t_way**)malloc(sizeof(t_way*) * graph->numb_ways);
	graph->len_ways = lenght_ways(res, graph->numb_ways);
	start_begin(graph, start, begin, res);
	choose_ways(info, graph, start, transp);
	run(transp, info, begin, graph);
	free(transp);
	free(begin);
	free(start);
}