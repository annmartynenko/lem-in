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
	printf("C\n");
	while (lst)
	{
		printf("D\n");
		i++;
		lst = lst->after;
	}
	printf("Q\n");
	return (i);
}

void	choose_ways(t_ways *result, t_inf *info)
{
	t_ways	*previous;
	t_ways	*current;
	t_ways	*future;
	int		i;
	int 	len;

	previous = result;
	printf("a\n");
//	printf("RESULT: %d\n", result->ways->content);
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
		printf("B len %d\n", len);
		while (current->ways)
		{
			printf("CURRENT: %d, FUTURE: %d\n", current->ways->content, future->ways->content);
			if (current->ways->content == future->ways->content)
				i++;
			current->ways = current->ways->after;
		}
//		if (i == len)
//		{
//			lstdel(current);
//			lstdelone(&previous, &current, future);
//		}
		result = result->next;
	}
}

void    move_ants(t_ways *queue, int numb, t_inf *info)
{
    t_way		*start;
    int         *len;
    int i;

    i = 0;
    len = (int*)malloc(sizeof(int) * numb);
    while (queue)
    {
        start = queue->ways;
        while (start)
        {
            start = start->after;
            len[i]++;
        }
        printf(" i %d, len %d\n", len[i], i);
        printf("result %s\n", info->room[start->content].name);
        i++;
        queue = queue->next;
    }
}