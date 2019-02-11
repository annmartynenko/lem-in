/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 16:53:21 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/31 16:53:22 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

//void	lstdelone(t_ways **previous, t_ways **current, t_ways *future)
//{
//	if (current && (*current))
//	{
//		(*previous) = (future);
//		free((*current));
//		(*current) = NULL;
//	}
//}
//
//void	lstdel(t_way **alst)
//{
//	t_way *a;
//
//	if (alst && (*alst))
//	{
//		while ((*alst) != NULL)
//		{
//			a = (*alst)->after;
//			free((*alst));
//			(*alst) = a;
//		}
//		(*alst) = NULL;
//	}
//}
//
//int 	lst_len(t_way *lst)
//{
//	int i;
//
//	i = 0;
//	while (lst)
//	{
//		i++;
//		lst = lst->after;
//	}
//	return (i);
//}

//void	choose_ways(t_ways *result, t_inf *info)
//{
//	t_ways	*previous;
//	t_ways	*current;
//	t_ways	*future;
//	t_ways	*begin;
//	int		i;
//	int 	len;
//
//	i = 0;
//	begin = result;
//	previous = NULL;
//	current = result;
//	future = result->next;
//	printf("a\n");
//	len = lst_len(current->ways);
//	while (result)
//	{
//		while (current)
//		{
//			if (current->ways->content == future->ways->content)
//				i++;
//			current->ways = current->ways->after;
//		}
//		result = result->next;
//	}
	/*
	while (result)
	{
//		printf("A\n");
//		printf("RESULT: %d\n", result->ways->content);
		current = result;
		if (result->next != NULL)
		{
			future = result->next;
			printf("FUTURE: %d\n",  future->ways->content);
		}
		printf("PREVIOUS: %d, \n", previous->ways->content);
		printf("CURRENT: %d, \n", current->ways->content);

		len = lst_len(current->ways);
		printf("len %d\n", len);
		while (current->ways)
		{
			printf("CURRENT: %d, FUTURE: %d\n", current->ways->content, future->ways->content);
			if (current->ways->content == future->ways->content)
				i++;
			current->ways = current->ways->after;
		}
		if (i == len)
		{
			lstdel(&current);
			lstdelone(&previous, &current, future);
		}
		result = result->next;
	}*/
//}
int 	*len_ways(t_ways *res, int numb)
{
	t_way		*start;
	int         *len;
	int i;

	i = 0;
	len = (int*)malloc(sizeof(int) * numb + 1);
	printf("NUMB %d\n", numb);
	while (res)
	{
		start = res->ways;
		while (start)
		{
			printf("start %d \n", start->content);
			start = start->after;
			len[i]++;
		}
		len[i] -= 2;
		printf(" i %d, len[%d]\n", len[i], i);
		i++;
		res = res->next;
	}
	len[i] = 0;
	return (len);
}

int 	how_much(int *len, int j)
{
	int how;
	int lenght;

	how = 0;
//	printf("j %d \n", j);
	lenght = len[j];
	while (j >= 0)
	{
		how += lenght - len[j];
		j--;
	}
//	printf("len %d\n", how);
	return (how);
}

//void	other_ants(int ant, int j, t_way **begin, t_inf *info, int star)
//{
//	int i;
//	int k;
//	t_way	**start;
//	t_way	**a;
//
//	i = 1;
//	k = 0;
//	a = begin;
//	start = begin;
//	while (i < ant)
//	{
//		k = 0;
//		if (a[k]->content == star)
//			a[k] = a[k]->after;
//		if (a[k]->after == NULL)
//			a[k] = start[k];
//		while (k <= j)
//		{
//			if (a[k]->content == star)
//				a[k] = a[k]->after;
//			if (a[k]->after == NULL)
//				a[k] = start[k];
//			else
//				a[k] = a[k]->after;
//			ft_printf("L");
//			ft_printf("%d-%s i%d k%d ", i, info->room[a[k]->content].name,i,k);
//			k++;
//		}
//		i++;
//	}
//}

void	run(t_moving *transp, t_inf *info, t_way **start, t_graph *graph)
{
	int i;
	int k;
	int d;
	int j;
	t_way *buf[graph->len_way];

	i = 0;
	d = 0;
	j = 0;
	k = 0;
	while (d < graph->len_way)
	{
		buf[d] = start[d];
		d++;
	}
	while (transp[info->ants - 1].room != graph->end)
	{
		d = transp[k].way;
		start[d] = buf[d];
		while (start[d]->content != transp[k].room)
			start[d] = start[d]->after;
		while (start[d]->content == graph->end && transp[k].room == graph->end)
			k++;
		if (start[d]->ant == -1)
		{

			ft_printf("L");
			ft_printf("%d-%s\n", transp[k].ant, info->room[start[d]->content].name);
			graph->nodes[transp[k].ant].room = start[d]->content;
			start[d]->ant = transp[k].ant;
			transp[k].room = start[d]->content;
			k = 0;
		}
		else if (start[d]->ant == transp[k].ant)
		{
			start[d]->ant = -1;
			start[d] = start[d]->after;
			ft_printf("L");
			ft_printf("%d-%s", transp[k].ant, info->room[start[d]->content].name);
			if (k == info->ants - 1)
				ft_printf("\n");
			else
				ft_printf(" ");
			graph->nodes[transp[k].ant].room = start[d]->content;
			start[d]->ant = transp[k].ant;
			transp[k].room = start[d]->content;
			k++;
		}
		if (k == info->ants)
			k = 0;
	}
}

void    move_ants(t_ways *res, t_inf *info, t_graph *graph)
{
	t_way	*start[graph->len_way];
	t_way	*begin[graph->len_way];
	t_moving	transp[info->ants];
	int 	*len;
	int		i;
	int		j;
	int		k;
	int 	ants;

	i = 0;
	j = 0;
	k = 0;
	ants = info->ants;
	len = len_ways(res, graph->len_way);
	while (i < graph->len_way)
	{
		start[i] = res->ways;
		begin[i] = res->ways;
		res = res->next;
		i++;
	}
	i = 0;
	while (i < info->ants)
	{
		j = 0;
		while (j < graph->len_way)
		{
			if (ants > how_much(len, j))
			{
				if (start[j]->content == graph->start)
					start[j] = start[j]->after;
				transp[k].room = start[j]->content;
				transp[k].ant = i + 1;
				transp[k].way = j;
				printf("ant %d, way %d\n", transp[k].ant, transp[k].way);
				ants--;
				i++;
				k++;
			}
			else if (i == info->ants - 1)
				break;
			j++;
		}
		if (i == info->ants - 1)
		{
			if (start[0]->content == graph->start)
				start[0] = start[0]->after;
			transp[k].room = start[0]->content;
			transp[k].ant = i + 1;
			transp[k].way = 0;
		}
	}
	run(transp, info, begin, graph);
}