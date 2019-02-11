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
	len = (int*)malloc(sizeof(int) * numb + 1);
	printf("NUMB %d\n", numb);
	while (res)
	{
		start = res->ways;
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
	return (len);
}

int 	how_much(int *len, int j)
{
	int how;
	int lenght;

	how = 0;
	lenght = len[j];
	while (j >= 0)
	{
		how += lenght - len[j];
		j--;
	}
	return (how);
}

void	print(t_moving *transp, t_way *start, t_inf *info)
{
	ft_printf("L");
	ft_printf("%d-%s ", (*transp).ant, info->room[start->content].name);
	start->ant = (*transp).ant;
	(*transp).room = start->content;
}

void	first_action(t_moving *transp, t_way **start, t_graph *graph, int *k)
{
	while ((*start)->content != transp[(*k)].room)
		(*start) = (*start)->after;
	while ((*start)->content == graph->end && transp[(*k)].room == graph->end)
		(*k)++;
}

void	fill_buf(t_graph *graph, t_way **start, t_way **buf)
{
	int d;

	d = 0;
	while (d < graph->numb_ways)
	{
		buf[d] = start[d];
		d++;
	}
}

void	run(t_moving *transp, t_inf *info, t_way **start, t_graph *graph)
{
	int k;
	int d;
	t_way *buf[graph->numb_ways];

	d = 0;
	k = 0;
	fill_buf(graph, start, &buf);
	while (transp[info->ants - 1].room != graph->end)
	{
		if (k == info->ants)
			k = 0;
		d = transp[k].way;
		start[d] = buf[d];
		first_action(transp, &start[d], graph, &k);
		if (k == info->ants || (start[d]->ant != -1 && start[d]->ant != transp[k].ant))
		{
			ft_printf("\n");
			k = 0;
		}
		d = transp[k].way;
		start[d] = buf[d];
		first_action(transp, &start[d], graph, &k);
		if (start[d]->ant == -1)
		{
			print(&transp[k], start[d], info);
			k++;
		}
		else if (start[d]->ant == transp[k].ant)
		{
			start[d]->ant = -1;
			start[d] = start[d]->after;
			print(&transp[k], start[d], info);
			k++;
		}
	}
}

void	fill_transp(t_moving *transp, t_way **start, int i, int j)
{
	(*transp).room = start[j]->content;
	(*transp).ant = i + 1;
	(*transp).way = j;
}

void	start_begin(t_graph *graph, t_way **start, t_way **begin, t_ways *res)
{
	int i;

	i = 0;
	while (i < graph->numb_ways)
	{
		start[i] = res->ways;
		begin[i] = res->ways;
		res = res->next;
		i++;
	}
}

void	if_start(t_way **start, t_graph *graph, int j)
{
	if (start[j]->content == graph->start)
		start[j] = start[j]->after;
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
				if_start(&start, graph, j);
				fill_transp(&transp[k], start, i, j);
				printf("ant %d, way %d\n", transp[k].ant, transp[k].way);
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
			if_start(&start, graph, 0);
			fill_transp(&transp[k], start, i, 0);
		}
	}
}

void    move_ants(t_ways *res, t_inf *info, t_graph *graph)
{
	t_way		*start[graph->numb_ways];
	t_way		*begin[graph->numb_ways];
	t_moving	transp[info->ants];

	graph->len_ways = lenght_ways(res, graph->numb_ways);
	start_begin(graph, &start, &begin, res);
	choose_ways(info, graph, &start, &transp);
	run(transp, info, begin, graph);
}