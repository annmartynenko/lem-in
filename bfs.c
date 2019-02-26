/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:53:33 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/22 15:53:34 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

void	copy_way(t_ways *queue, t_way *prev, int neighbor, t_inf *info, t_graph * graph)
{
	t_way		*buf;
	t_ways		*tmp;

	tmp = queue;
	if (tmp->next != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	(tmp)->next = (t_ways*)malloc(sizeof(t_ways));
	(tmp) = tmp->next;
	tmp->next = NULL;
	tmp->ways = (t_way*)malloc(sizeof(t_way));
	buf = tmp->ways;
	while ((prev))
	{
		buf->content = (prev)->content;
		printf("%s(%d)-", info->room[buf->content].name, graph->nodes[buf->content].searched);
		buf->ant = -1;
		buf->after = (t_way*)malloc(sizeof(t_way));
		buf = buf->after;
		prev = (prev)->after;
	}
	buf->content = neighbor;
	printf("%s(%d)\n", info->room[buf->content].name, graph->nodes[buf->content].searched);
	buf->ant = -1;
	buf->after = NULL;
}

void	fill_ways(t_way *start, t_ways **result, t_graph *graph, t_inf *info)
{
	t_way		*buf;

	graph->numb_ways++;
	if ((*result)->next == NULL && graph->numb_ways > 1)
	{
		(*result)->next = (t_ways*)malloc(sizeof(t_ways));
		(*result) = (*result)->next;
		(*result)->next = NULL;
	}
	(*result)->ways = (t_way*)malloc(sizeof(t_way));
	(*result)->next = NULL;
	buf = (*result)->ways;
	while (start)
	{
		buf->content = start->content;
		if (start->content != (graph)->end && start->content != (graph)->start)
			(graph)->nodes[buf->content].note = 1;
		printf("%s(%d) - ", info->room[buf->content].name, graph->nodes[buf->content].searched);
		buf->ant = -1;
		buf->after = (t_way*)malloc(sizeof(t_way));
		buf = buf->after;
		start = start->after;
	}
	buf->content = (graph)->end;
	printf("%s(%d)\n", info->room[buf->content].name, graph->nodes[buf->content].searched);
	buf->ant = -1;
	buf->after = NULL;
}

void	check_edges(t_graph *graph, t_way *start, t_ways *queue, t_ways **result, t_inf *info)
{
	int j;

	j = -1;
	while (graph->nodes[graph->current].edges[++j] != -1)
	{
		graph->neighbor = graph->nodes[graph->current].edges[j];
		if (graph->neighbor != graph->start &&\
			check_searched(start, graph) && graph->nodes[graph->neighbor].searched == -1)
		{
			if (graph->neighbor != graph->end)
				copy_way(queue, start, graph->neighbor, info, graph);
			else if (graph->neighbor == graph->end)
				fill_ways(start, result, graph, info);
		}
	}
}

void	bfs(t_graph *graph, t_inf *info)
{
	t_ways		*queue;
	t_way		*start;
	t_ways		*tmp123;
	t_ways		*result;
	t_ways		*res;

	result = (t_ways*)malloc(sizeof(t_ways));
	res = result;
	queue = create_queue(graph);
	while (queue)
	{
		start = queue->ways;
		move_and_check(queue, graph);
		printf("%s(%d)\n", info->room[graph->current].name, graph->nodes[graph->current].searched);
		check_edges(graph, start, queue, &result, info);
		tmp123 = queue->next;
		clean_start(start);
		free(queue);
		queue = tmp123;
	}
	conditions(graph, info, res);
	move_ants(res, info, graph);
	clean_res(res);
}
