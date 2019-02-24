/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:45:31 by amartyne          #+#    #+#             */
/*   Updated: 2019/02/24 16:45:32 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

int		check_searched(t_way *start, t_graph *graph)
{
	while (start)
	{
		if (start->content != graph->start && start->content\
		!= graph->end && graph->nodes[start->content].note == 1)
			return (0);
		start = start->after;
	}
	return (1);
}

void	move_and_check(t_ways *queue, t_graph *graph)
{
	while (queue->ways && queue->ways->after)
		queue->ways = queue->ways->after;
	graph->current = queue->ways->content;
	if (graph->nodes[graph->current].searched != 1 &&\
	graph->current != graph->start && graph->current != graph->end)
		graph->nodes[graph->current].searched = 1;
}

t_ways	*create_queue(t_graph *graph)
{
	t_ways		*queue;

	graph->nodes[graph->start].searched = -1;
	queue = (t_ways*)malloc(sizeof(t_ways));
	queue->ways = (t_way*)malloc(sizeof(t_way));
	queue->ways->content = graph->start;
	queue->ways->after = NULL;
	queue->next = NULL;
	return (queue);
}

void	conditions(t_graph *graph, t_inf *info, t_ways *res)
{
	if (graph->numb_ways == 0)
		exit_l("no ways found");
	if (info->ways == 1)
		print_ways(res, info);
}
