/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:07:05 by amartyne          #+#    #+#             */
/*   Updated: 2019/02/12 17:07:06 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

int 	how_much(int *len, int j)
{
	int how;
	int lenght;

	how = 0;
	lenght = len[j];
	while (j >= 0)
	{
		how += lenght - len[j];
		j--;
	}
	return (how);
}

void	print(t_moving *transp, t_way *start, t_inf *info, int *k)
{
	ft_printf("L");
	ft_printf("%d-%s ", (*transp).ant, info->room[start->content].name);
	start->ant = (*transp).ant;
	(*transp).room = start->content;
	(*k)++;
}

void	first_action(t_moving *transp, t_way **start, t_graph *graph, int *k)
{
	while ((*start)->content != transp[(*k)].room)
		(*start) = (*start)->after;
	while ((*start)->content == graph->end && transp[(*k)].room == graph->end)
		(*k)++;
}

void	fill_buf(t_graph *graph, t_way **start, t_way **buf)
{
	int d;

	d = 0;
	while (d < graph->numb_ways)
	{
		buf[d] = start[d];
		d++;
	}
}

void	new_line(int *k)
{
	ft_printf("\n");
	(*k) = 0;
}