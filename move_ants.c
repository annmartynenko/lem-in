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

	how = len[j] - 1;
	while (j >= 1)
	{
		how += len[j] - len[j - 1];
		j--;
	}
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

void	run(t_moving *transp, t_inf *info, int ants, t_way **start, t_graph *graph)
{
	int		i;
	int		k;
	int		d;
	int		j;
	t_way	*buf;
	t_moving	*tmp;

	i = 0;
	d = 0;
	j = 0;
	tmp = transp;
	buf = start[d];
	while (j < ants - 1)
	{
		i = 0;
		transp = tmp;
		while (i < ants && transp)
		{
			d = transp->way;
			if (start[d] == NULL)
				start[d] = buf;
			while (start[d]->content != transp->room)
				start[d] = start[d]->after;
			ft_printf("L");
			ft_printf("%d-%s\n", transp->ant, info->room[start[d]->content].name);
			if (start[d]->after)
				transp->room = start[d]->after->content;
			i++;
			transp = transp->next;
		}
		j++;
	}
}

void    move_ants(t_ways *res, int numb, t_inf *info, t_graph *graph)
{
	t_way	*start[numb];
	t_way	*begin[numb];
	t_moving	*transp;
	t_moving	*tr;
	int 	*len;
	int		i;
	int		j;
	int 	ants;

	i = 0;
	j = 0;
	transp = (t_moving*)malloc(sizeof(t_moving));
	tr = transp;
	ants = info->ants;
	len = len_ways(res, numb);
	while (i < numb)
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
		while (j < numb)
		{
			if (ants > how_much(len, j))
			{
//				printf("\n{ begin before %s, start before %s , j %d}\n", \
//				info->room[begin[j]->content].name, info->room[start[j]->content].name, j);
//				other_ants(i + 1, j, begin, info, graph->start);
//				printf("\n{ begin after %s, start after %s, j %d }\n", \
//				info->room[begin[j]->content].name,info->room[start[j]->content].name, j);
//				ft_printf("L");
				if (start[j]->content == graph->start)
					start[j] = start[j]->after;
				transp->room = start[j]->content;
				transp->ant = i + 1;
				transp->way = j;
//				printf("room %s, ant %d, way %d\n", info->room[transp->room].name, transp->ant, transp->way);
				transp->next = (t_moving*)malloc(sizeof(t_moving));
				transp = transp->next;
				transp->next = NULL;
//				ft_printf("%d-%s j%d\n", i + 1, info->room[start[j]->content].name, j);
				ants--;
				i++;
			}
			else if (i == info->ants - 1)
				break;
			j++;
		}
		if (i == info->ants - 1)
		{
//			other_ants(i + 1, j, begin, info, graph->start);
//			ft_printf("L");
			if (start[0]->content == graph->start)
				start[0] = start[0]->after;
			transp->room = start[0]->content;
			transp->ant = i + 1;
			transp->way = 0;
//			printf("room %d, ant %d, way %d\n", transp->room, transp->ant, transp->way);
			transp->next = (t_moving*)malloc(sizeof(t_moving));
			transp = transp->next;
			transp->next = NULL;
//			ft_printf("%d-%s\n", i + 1, info->room[start[0]->content].name);
			ants--;
			break;
		}
	}
	run(tr, info, info->ants, begin, graph);
}