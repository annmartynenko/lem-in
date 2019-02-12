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

void	fill_node(t_graph **graph, int i, int *k, int paste)
{
	(*graph)->nodes[i].edges[*k] = paste;
	if (!(*graph)->nodes[i].searched && !(*graph)->nodes[i].parent)
	{
		(*graph)->nodes[i].searched = -1;
		(*graph)->nodes[i].parent = -1;
	}
	printf("val %d, edg %d, sear %d, parent %d\n", (*graph)->nodes[i].value, (*graph)->nodes[i].edges[*k], (*graph)->nodes[i].searched, (*graph)->nodes[i].parent);
	(*k)++;

}

void	find_se(t_graph **graph, t_inf * info)
{
	int i;

	i = 0;
	while (i < info->rooms)
	{
		if (info->room[i].s_e == START)
			(*graph)->start = i;
		else if (info->room[i].s_e == END)
			(*graph)->end = i;
		i++;
	}
	(*graph)->numb_ways = 0;
	printf("end %d: start %d\n", (*graph)->end, (*graph)->start);
}

int     count_adges(t_inf *info, int i)
{
    int j;
    int len;

    j = 0;
    len = 0;
    while (j < info->links)
    {
        if (info->link[j].rm1 == i || info->link[j].rm2 == i)
            len++;
        j++;
    }
    return (len);
}

void	make_graph(t_inf *info)
{
	int i;
	int j;
	int k;
	t_graph *graph;

	graph = (t_graph*)malloc(sizeof(t_graph));
	graph->nodes = (t_node*)malloc(sizeof(t_node) * info->rooms);
	graph->end = -1;
	graph->start = -1;
	i = 0;
	printf("HELLO\n");
	while (i < info->rooms)
	{
		graph->nodes[i].value = i;
		graph->nodes[i].n_edg = count_adges(info, i);
		printf("number edges for %d = %d\n", i, graph->nodes[i].n_edg);
		graph->nodes[i].edges = (int*)malloc(sizeof(int) * graph->nodes[i].n_edg + 1);
		j = 0;
		k = 0;
		while (j < info->links)
		{
			if (graph->nodes[i].value == info->link[j].rm1)
				fill_node(&graph, i, &k, info->link[j].rm2);
			else if (graph->nodes[i].value == info->link[j].rm2)
				fill_node(&graph, i, &k, info->link[j].rm1);
			j++;
		}
		(graph)->nodes[i].edges[k] = -1;
		printf("val %d, edg %d, sear %d, parent %d\n", (graph)->nodes[i].value, (graph)->nodes[i].edges[k], (graph)->nodes[i].searched, (graph)->nodes[i].parent);
		k++;
		i++;
	}
	find_se(&graph, info);
	printf("\n%d: %d | %d %d\n", graph->nodes[2].value, graph->nodes[2].edges[0], (graph)->nodes[2].searched, (graph)->nodes[2].parent);
	bfs(graph, info);
}