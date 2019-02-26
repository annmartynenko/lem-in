/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:09:27 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/22 13:09:28 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

t_graph	*create_graph(t_inf *info)
{
	t_graph *graph;

	graph = (t_graph*)malloc(sizeof(t_graph));
	graph->nodes = (t_node*)malloc(sizeof(t_node) * info->rooms);
	graph->end = -1;
	graph->start = -1;
	graph->numb_ways = 0;
	graph->len_ways = NULL;
	graph->current = 0;
	graph->neighbor = 0;
	graph->lines = 0;
	graph->ants = 0;
	graph->d = 0;
	graph->parent = 0;
	return (graph);
}

void	make_graph(t_inf *info)
{
	int			i;
	t_graph		*graph;

	i = -1;
	graph = create_graph(info);
	while (++i < info->rooms)
	{
		graph->nodes[i].value = i;
		graph->nodes[i].n_edg = count_edges(info, i);
		graph->nodes[i].edges = (int*)malloc(sizeof(int) *\
		(graph->nodes[i].n_edg + 1));
		links(graph, info, i);
	}
	find_se(&graph, info);
	bfs(graph, info);
	i = -1;
	while (++i < info->rooms)
		free(graph->nodes[i].edges);
	free(graph->nodes);
	free(graph->len_ways);
	free(graph);
}
