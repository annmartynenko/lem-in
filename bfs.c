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

void	copy_way(t_ways *queue, t_way *prev, int neighbor)
{
	t_way *buf;
	t_way *tmp;

	tmp = prev;
	if (queue->next != NULL)
	{
		while (queue->next)
			queue = queue->next;
	}

	(queue)->next = (t_ways*)malloc(sizeof(t_ways));
	(queue) = (queue)->next;
	(queue)->next = NULL;
	(queue)->ways = (t_way*)malloc(sizeof(t_way));
	buf = (queue)->ways;
	while ((prev))
	{
		buf->content = (prev)->content;
		buf->ant = -1;
		buf->after = (t_way*)malloc(sizeof(t_way));
		buf = buf->after;
		prev = (prev)->after;
	}
	buf->content = neighbor;
	buf->ant = -1;
	buf->after = NULL;
	while (tmp)
	{
		buf = tmp->after;
		free(tmp);
		tmp = buf;
	}
}

int		check_neighbor(t_way *start, int neighbor)
{
	while (start)
	{
		if (start->content == neighbor)
			return (0);
		start = start->after;
	}
	return (1);
}

void	fill_ways(t_way *start, t_ways **result, t_inf *info, t_graph **graph)
{
	t_way		*buf;
//	t_way		*tmp;

	buf = start;
	start = start->after;
	while (start->after)
	{
		if ((*graph)->nodes[start->content].searched != -1)
			break;
		start = start->after;
	}
	printf("start %s\n", info->room[start->content].name);
	if (start->content == (*graph)->end)
	{
		start = buf;
		(*graph)->numb_ways++;
		if ((*result)->next == NULL && (*graph)->numb_ways > 1)
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
			if (start->content != (*graph)->end)
				(*graph)->nodes[start->content].searched = 1;
			buf->ant = -1;
			printf(" %s / ", info->room[buf->content].name);
			if (start->after)
			{
				buf->after = (t_way*)malloc(sizeof(t_way));
				buf = buf->after;
			}
			start = start->after;
		}
		printf("\n");
		buf->after = NULL;
	}
}

void	bfs(t_graph *graph, t_inf *info)
{
	{
		t_ways *queue;
		t_way *start;
		t_way *tmp;
		void *tmp123;
		int current;
		int j;
		int neighbor;
		int papa;
		t_ways *result;
		t_ways *res;

		result = (t_ways *) malloc(sizeof(t_ways));
		res = result;
		graph->nodes[graph->start].searched = 1;
		queue = (t_ways *) malloc(sizeof(t_ways));
		queue->ways = (t_way *) malloc(sizeof(t_way));
		queue->ways->content = graph->start;
		queue->ways->after = NULL;
		queue->next = NULL;
		printf("queue1 %d\n", queue->ways->content);
		while (queue)
		{
			start = queue->ways;
			printf("WAY ");
			while (queue->ways && queue->ways->after)
			{
				printf("%s->", info->room[queue->ways->content].name);
				papa = queue->ways->content;
				queue->ways = queue->ways->after;
			}
			printf("%s->", info->room[queue->ways->content].name);
			printf("\n");
			current = queue->ways->content;
			j = 0;
			if (current != graph->end)
			{
				while (graph->nodes[current].edges[j] != -1)
				{
					neighbor = graph->nodes[current].edges[j];
					if (papa != neighbor && neighbor != graph->start && check_neighbor(start, neighbor))
					{
						copy_way(queue, start, neighbor);
//					if (neighbor != graph->end)
//						graph->nodes[neighbor].searched = 1;
					}
					j++;
				}
			}
			if (current == graph->end)
			{
				printf("FOUND %s\n", info->room[current].name);
				fill_ways(start, &result, info, &graph);
				printf("len %d\n", graph->numb_ways);
			}
//		if ((graph)->numb_ways == 500)
//			exit(0);
			tmp123 = queue->next;
			free(queue);                                // KOCTUL
			queue = (t_ways *) tmp123;
		}
//	while (res)
//	{
//		while (res->ways)
//		{
//			printf("%s - ", info->room[res->ways->content].name);
//			res->ways = res->ways->after;
//		}
//		printf("\n");
//		res = res->next;
//
//	                                   }
		move_ants(res, info, graph);
//	free(res); // ???????????????????????!!!!!!!!!!!!!!!!!!!
//	res = NULL;
		system("leaks lem-in");
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
			res = (t_ways *) tmp123;
//		res = res->next;
		}


		while (start)
		{
			tmp = start->after;
			free(start);
			start = tmp;
		}
	}
//	printf("*****************%p\n", queue);
//	printf("*****************%p\n", start);
//	printf("*****************%p\n", tmp);
//	printf("*****************%p\n", res);
//	printf("*****************%p\n", result);

}
