/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:09:36 by amartyne          #+#    #+#             */
/*   Updated: 2019/02/12 17:09:37 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

void	fill_transp(t_moving *transp, int room, int i, int j)
{
	(transp)->room = room;
	(transp)->ant = i + 1;
	(transp)->way = j;
}

void	start_begin(t_graph *graph, t_way ***start, t_way ***begin, t_ways *res)
{
	int i;

	i = 0;
	while (i < graph->numb_ways)
	{
		(*start)[i] = res->ways;
		(*begin)[i] = res->ways;
		res = res->next;
		i++;
	}
}

void	if_start(t_way **start, t_graph *graph, int j)
{
	if ((start)[j]->content == graph->start)
		(start)[j] = (start)[j]->after;
}