/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 12:55:58 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/21 12:55:59 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

void    same_rooms(t_inf *info, int j)
{
    int i;

    i = 0;
    while (i < j)
    {
        if (ft_strcmp(info->room[j].name, info->room[i].name) == 0)
            exit_l("the same names of rooms");
        if (info->room[j].x == info->room[i].x && \
        info->room[j].y == info->room[i].y)
            exit_l("rooms with the same coordinates ");
        i++;
    }
}

void	write_room(t_fl *file, t_inf *info, int a, int *j)
{
	char **mass;

	mass = ft_strsplit(file->line, ' ');
	info->room[(*j)].name = ft_strdup(mass[0]);
	info->room[(*j)].x = ft_atoi(mass[1]);
	info->room[(*j)].y = ft_atoi(mass[2]);
    same_rooms(info, (*j));
	info->room[(*j)].s_e = a;
	ft_arrfree(mass);
	printf("%s %d %d | %d %d\n", info->room[*j].name, info->room[*j].x, info->room[*j].y, *j, info->room[*j].s_e);
	(*j)++;
}

void	write_link(t_fl *file, t_inf *info, int *i)
{
	char **mass;
	int j;

	j = 0;
	info->link[(*i)].rm1 = -1;
	info->link[(*i)].rm2 = -1;
	mass = ft_strsplit(file->line, '-');
	while (j < info->rooms)
	{
		if (ft_strcmp(mass[0], info->room[j].name) == 0)
			info->link[(*i)].rm1 = j;
		else if (ft_strcmp(mass[1], info->room[j].name) == 0)
			info->link[(*i)].rm2 = j;
		j++;
	}
	if (info->link[*i].rm1 == -1 || info->link[*i].rm2 == -1 || \
	info->link[*i].rm1 == info->link[*i].rm2)
		exit_l("non-existent room in link");
	ft_arrfree(mass);
	printf("%d-%d \n", info->link[(*i)].rm1, info->link[(*i)].rm2);
	(*i)++;
}

void	parsing(t_fl *file, t_inf *info)
{
	int i;
	int j;
	int s_e;
//	t_fl *tmp;

	j = 0;
	i = 0;
	s_e = 0;
	info->room = (t_room*)malloc(sizeof(t_room) * info->rooms);
	info->link = (t_link*)malloc(sizeof(t_room) * info->links);
	while (file && file->next)
	{
		if (ft_strcmp(file->line, "##start") == 0)
		{
			file = file->next;
			write_room(file, info, START, &j);
			s_e++;
		}
		else if (ft_strcmp(file->line, "##end") == 0)
		{
			file = file->next;
			write_room(file, info, END, &j);
			s_e++;
		}
		else if (ft_strchr(file->line, ' ') && file->line[0] != '#')
			write_room(file, info, NORMAL, &j);
		else if (ft_strchr(file->line, '-'))
			write_link(file, info, &i);
		file = file->next;
	}
	printf("PPP\n");
	if (s_e != 2)
		exit_l("no start or end mark");
//	free(file);
//	while (file)
//	{
//		tmp = file->next;
//		free(file->line);
//		free(file);
//		file = tmp;
//		file = file->next;
//	}
}