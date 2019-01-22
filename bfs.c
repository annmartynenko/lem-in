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

size_t	ft_intlen(int *s)
{
	size_t i;

	i = 0;
	if (s == NULL || s[i] == '\0')
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	*ft_intjoin(int *s1, int s2)
{
	int	*a;
	size_t	i;
	size_t	l1;

	i = 0;
	a = NULL;
	l1 = ft_intlen(s1);
	a = (int*)malloc(l1 + 2);
	if (!a)
		return (NULL);
	while (i < l1)
	{
		a[i] = s1[i];
		i++;
	}
	a[i++] = s2;
	a[i] = '\0';
	return (a);
}

void	bfs(t_graph *graph, t_inf *info)
{
	int		*queue;
	int		i;
	int		current;
	int		j;
	int neighbor;

	i = 0;
	printf("\n%d: %d | %d %d\n", graph->nodes[2].value, graph->nodes[2].edges[0], (graph)->nodes[2].searched, (graph)->nodes[2].parent);
	graph->nodes[graph->start].searched = 1;
	printf("\n%d: %d | %d %d\n", graph->nodes[2].value, graph->nodes[2].edges[0], (graph)->nodes[2].searched, (graph)->nodes[2].parent);
	queue = (int*)malloc(sizeof(int) * 2);
	if (graph->start == 0)
		queue[0] = 0;
	else
		queue[0] = graph->start;
	queue[1] = '\0';
	printf("len %zd\n", ft_intlen(queue));
	printf("queue[0] %d\n", queue[0]);
	while (i < 4)
	{
		current = queue[i];
		printf("current %d\n", current);
		if (current == graph->end)
		{
			printf("Found %s\n", info->room[current].name);
			break;
		}
		j = 0;
		while (graph->nodes[current].edges[j])
		{
			neighbor = graph->nodes[current].edges[j];
			printf("current %d, search %d, edge %d\n", current, graph->nodes[neighbor].searched, neighbor);
			if (graph->nodes[j].searched != 1)
			{
				graph->nodes[neighbor].searched = 1;
				graph->nodes[neighbor].parent = current;
				queue = ft_intjoin(queue, neighbor);
				printf("new q %d\n", queue[i + 1]);
			}
			j++;
		}
		i++;
	}
}
