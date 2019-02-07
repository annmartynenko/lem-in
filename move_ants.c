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

void	lstdelone(t_ways **previous, t_ways **current, t_ways *future)
{
	if (current && (*current))
	{
		(*previous) = (future);
		free((*current));
		(*current) = NULL;
	}
}

void	lstdel(t_way **alst)
{
	t_way *a;

	if (alst && (*alst))
	{
		while ((*alst) != NULL)
		{
			a = (*alst)->after;
			free((*alst));
			(*alst) = a;
		}
		(*alst) = NULL;
	}
}

int 	lst_len(t_way *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->after;
	}
	return (i);
}

void	choose_ways(t_ways *result, t_inf *info)
{
	t_ways	*previous;
	t_ways	*current;
	t_ways	*future;
	t_ways	*begin;
	int		i;
	int 	len;

	i = 0;
	begin = result;
	previous = NULL;
	current = result;
	future = result->next;
	printf("a\n");
	len = lst_len(current->ways);
	while (result)
	{
		while (current)
		{
			if (current->ways->content == future->ways->content)
				i++;
			current->ways = current->ways->after;
		}
		result = result->next;
	}
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
}
int 	*len_ways(t_ways *res, int numb, t_inf *info)
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
	while (j > 1)
	{
		how += len[j] - len[j - 1];
		j--;
	}
	return (how);
}

void    move_ants(t_ways *res, int numb, t_inf *info, t_graph *graph)
{
	t_ways	*start[numb];
	t_ways	*begin[numb];
	int 	*len;
	int		i;
	int		j;
	int 	ants;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	ants = info->ants;
	len = len_ways(res, numb, info);
	while (i < numb)
	{
		start[i] = res;
		begin[i] = res;
		res = res->next;
		i++;
	}
	i = 0;
	while (i < info->ants)
	{
		j = 0;
		while (j < numb)
		{
			if (ants >= how_much(len, j))
			{
				ft_printf("L");
				if (start[j]->ways->content == graph->start)
					start[j]->ways = start[j]->ways->after;
				ft_printf("%d-%s\n", i, info->room[start[j]->ways->content].name);
				ants--;
				i++;
				if (i > 1)
				{
					k = j;
					while (k < i && begin[k]->ways)
					{
						ft_printf("L");
						if (begin[k]->ways->content == graph->start)
							begin[k]->ways = begin[k]->ways->after;
						ft_printf("%d-%s ", k, info->room[begin[k]->ways->content].name);
						begin[k]->ways = begin[k]->ways->after;
						k++;
					}
				}
//				start[j]->ways = start[j]->ways->after;
			}
			else
				break;
			j++;
		}
	}
}