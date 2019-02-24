/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:11:26 by amartyne          #+#    #+#             */
/*   Updated: 2019/02/24 17:11:27 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

void	fill_node(t_graph **graph, int i, int *k, int paste)
{
	(*graph)->nodes[i].edges[(*k)] = paste;
	(*graph)->nodes[i].searched = -1;
	(*graph)->nodes[i].note = -1;
	(*k)++;
}

void	find_se(t_graph **graph, t_inf *info)
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
}

int		count_edges(t_inf *info, int i)
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

void	links(t_graph *graph, t_inf *info, int i)
{
	int j;
	int k;

	j = -1;
	k = 0;
	while (++j < info->links)
	{
		if (graph->nodes[i].value == info->link[j].rm1)
			fill_node(&graph, i, &k, info->link[j].rm2);
		else if (graph->nodes[i].value == info->link[j].rm2)
			fill_node(&graph, i, &k, info->link[j].rm1);
	}
	(graph)->nodes[i].edges[k] = -1;
}
