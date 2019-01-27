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

void	copy_way(t_ways *queue, t_way *prev, int  neighbor)
{
	t_way		*buf;

	(queue)->next = (t_ways*)malloc(sizeof(t_ways));
	(queue) = (queue)->next;
	(queue)->next = NULL;
	(queue)->ways = (t_way*)malloc(sizeof(t_way));
	buf = (queue)->ways;
	while ((prev))
	{
		buf->content = (prev)->content;
		printf("wat %d\n", buf->content);
		buf->after = (t_way*)malloc(sizeof(t_way));
		buf = buf->after;
		prev = (prev)->after;
	}
	buf->content = neighbor;
	buf->after = NULL;
//	buf->ways = buf;
}

void	bfs(t_graph *graph, t_inf *info)
{
	t_ways		*queue;
	t_way		*start;
	int			current;
	int			j;
	int			neighbor;
	int i;

//	printf("\n%d: %d | %d %d\n", graph->nodes[2].value, graph->nodes[2].edges[0], (graph)->nodes[2].searched, (graph)->nodes[2].parent);
	graph->nodes[graph->start].searched = 1;
//	printf("\n%d: %d | %d %d\n", graph->nodes[2].value, graph->nodes[2].edges[0], (graph)->nodes[2].searched, (graph)->nodes[2].parent);
	queue = (t_ways*)malloc(sizeof(t_ways));
	queue->ways = (t_way*)malloc(sizeof(t_way));
//	start = queue;
	queue->ways->content = graph->start;
	printf("queue1 %d\n", queue->ways->content);
//	printf("start %d\n", start->ways->content);
	while (queue)
	{
		start = queue->ways;
		current = queue->ways->content;
		while (current != graph->end)
		{
			printf("Scurrent %s\n", info->room[current].name);
			j = 0;
			i = 0;
			while (graph->nodes[current].edges[j] != -1)
			{
				neighbor = graph->nodes[current].edges[j];

				printf("current %s, search %d, edge %s\n", info->room[current].name, graph->nodes[neighbor].searched,
					   info->room[neighbor].name);
				if (i >= 1)
					copy_way(queue, start, neighbor);
				if (graph->nodes[neighbor].searched != 1 && i < 1)
				{
					queue->ways->after = (t_way *) malloc(sizeof(t_way));
					queue->ways = queue->ways->after;
					queue->ways->content = neighbor;
					printf("neighbor %s\n", info->room[(queue)->ways->content].name);
					if (neighbor != graph->end)
						graph->nodes[neighbor].searched = 1;
					graph->nodes[neighbor].parent = current;
					i++;
				}
				j++;
			}
			current = queue->ways->content;
		}
		if (current == graph->end)
		{
			printf("Found %s\n", info->room[current].name);
			i = 0;
			while (start)
			{
				printf("result %s\n", info->room[start->content].name);
				start = start->after;
				i++;
			}
//			break;
		}
		queue = queue->next;
	}
}
