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

void	copy_way(t_ways *queue, t_way *prev, int neighbor, t_graph *graph)
{
	t_way *buf;
	t_ways *tmp;

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
		buf->ant = -1;
		printf(" %d(%d)-> ", buf->content, (graph)->nodes[prev->content].searched);
//		if (prev->content != (graph)->end && prev->content != (graph)->start)
//			(graph)->nodes[prev->content].searched = 1;
		buf->after = (t_way *) malloc(sizeof(t_way));
		buf = buf->after;
		prev = (prev)->after;
	}
	buf->content = neighbor;
	printf(" %d(%d)-> ", buf->content, (graph)->nodes[buf->content].searched);
	printf("\n");
//	(graph)->nodes[neighbor].searched = 1;
	buf->ant = -1;
	buf->after = NULL;
}

int		check_neighbor(t_way *start, int neighbor)
{
//	start = start->after;
	while (start)
	{
		if (start->content == neighbor)
			return (0);
		start = start->after;
	}
	return (1);
}

void	fill_ways(t_way *start, t_ways **result, t_inf *info, t_graph *graph)
{
	t_way		*buf;

	buf = NULL;
	printf("first element %s\n", info->room[start->content].name);
	(graph)->numb_ways++;
	if ((*result)->next == NULL && (graph)->numb_ways > 1)
	{
		(*result)->next = (t_ways*)malloc(sizeof(t_ways));
		(*result) = (*result)->next;
		(*result)->next = NULL;
	}
	(*result)->ways = (t_way*)malloc(sizeof(t_way));
	(*result)->next = NULL;
	printf("result");
	buf = (*result)->ways;
	while (start)
	{
		buf->content = start->content;
//		if (start->content != (graph)->end && start->content != (graph)->start)  //і сюди
//			(graph)->nodes[buf->content].searched = 1;
		buf->ant = -1;
		printf(" %d / ", buf->content);
		buf->after = (t_way*)malloc(sizeof(t_way));
		buf = buf->after;
		start = start->after;
	}
	buf->content = (graph)->end;
	buf->ant = -1;
	printf(" %d / ", buf->content);
	buf->after = NULL;
	printf("\n");

}

void	bfs(t_graph *graph, t_inf *info)
{
	t_ways *queue;
	t_way *start;
	t_way *tmp;
	t_ways *tmp123;
	int current;
	int j;
	int neighbor;
	int papa;
	t_ways *result;
	t_ways *res;

	result = (t_ways *) malloc(sizeof(t_ways));
	res = result;
//	papa = -1;
	graph->nodes[graph->start].searched = -1;
	queue = (t_ways *) malloc(sizeof(t_ways));
	queue->ways = (t_way *) malloc(sizeof(t_way));
	queue->ways->content = graph->start;
	queue->ways->after = NULL;
	queue->next = NULL;
	printf("queue1 %d\n", queue->ways->content);
	while (queue)
	{
		start = queue->ways;
		papa = -1;
		while (queue->ways && queue->ways->after)
		{
			papa = queue->ways->content;
			queue->ways = queue->ways->after;
		}
		current = queue->ways->content;
		if (current != (graph)->end && current != (graph)->start)
			(graph)->nodes[current].searched = 1;
		j = 0;
		while (graph->nodes[current].edges[j] != -1)
		{
			neighbor = graph->nodes[current].edges[j];
//			printf("%d - %d\n", neighbor, (graph)->nodes[neighbor].searched);
			if (papa != neighbor && neighbor != graph->start && check_neighbor(start, neighbor) && graph->nodes[neighbor].searched == -1)
			{
				if (neighbor != graph->end)
					copy_way(queue, start, neighbor, graph);
				else
					fill_ways(start, &result, info, graph);
			}
			j++;
		}
		tmp123 = queue->next;
		tmp = NULL;
		while (start)
		{
			tmp = start->after;
			free(start);
			start = tmp;
		}
		free(queue);
		queue = tmp123;
	}
	printf("BFS end\n");
	if (graph->numb_ways == 0)
		exit_l("no ways found");
	move_ants(res, info, graph);
	while (res)
	{
		tmp = res->ways;
		void *tmp321 = NULL;
		while (tmp)
		{
			tmp321 = tmp->after;
			free(tmp);
			tmp = tmp321;
		}
		tmp123 = res->next;
		free(res);                                // KOCTUL
		res = tmp123;
	}
}
