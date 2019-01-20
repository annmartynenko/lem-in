/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:04:26 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/18 15:04:27 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

void	parsing(t_fl *file, t_inf *info)
{
	int i;
	int j;
	char **for_volodya;

	i = 0;
	j = 0;
	info->room = (t_room*)malloc(sizeof(t_room) * info->rooms);
	info->link = (t_link*)malloc(sizeof(t_room) * info->links);
	while (file && file->next)
	{
		if (ft_strcmp(file->line, "##start") == 0)
		{
			file = file->next;
			for_volodya = ft_strsplit(file->line, ' ');
			info->room[j].name = ft_strdup(for_volodya[0]);
			info->room[j].x = ft_atoi(for_volodya[1]);
			info->room[j].y = ft_atoi(for_volodya[2]);
			info->room[j].s_e = START;
			printf("%s %d %d\n", info->room[j].name, info->room[j].x, info->room[j].y);
			exit(0);
		}
		file = file->next;
	}
}

int 	check_room(char *tmp)
{
	int i;
	int sp;

	i = 1;
	sp = 0;
	if(tmp[0] == '#')
		return(0);
	else if(tmp[0] == 'L')
		exit_l(4);
	while (tmp[i])
	{
		if (tmp[i] != ' ' && (sp == 1 || sp == 2) && !ft_isdigit(tmp[i]))
			exit_l(3);
		if (tmp[i] == ' ')
			sp++;
		if	(tmp[i] == '-')
			return  (0);
		if (sp > 3)
			exit_l(5);
		i++;
	}
	if (sp == 2)
		return (1);
	return (0);
}

void	check_ants(int fd, t_inf *info)
{
	char *tmp;
	int i;

	i= 0;
	get_next_line(fd, &tmp);
	if (!(info->ants = ft_atoi(tmp)))
		exit_l(1);
	while(tmp[i] && ft_isdigit(tmp[i]))
		i++;
	if (tmp[i] != '\0')
		exit_l(2);
}

int 	check_links(char *tmp)
{
	int i;
	int hyphen;

	i = 0;
	hyphen = 0;
	if(tmp[0] == '#')
		return(0);
	while (tmp[i])
	{
		if (tmp[i] == ' ')
			return (0);
		if (tmp[i] == '-')
			hyphen++;
		if(hyphen > 1)
			exit_l(8);
		i++;
	}
	if (hyphen == 0)
		return (0);
	return (1);
}

void	read_map(char **av, t_inf *info)
{
	char *tmp;
	int fd;
	t_fl *file;
	t_fl *buf;

	tmp = NULL;
	fd = open(av[1], O_RDONLY);
	check_ants(fd, info);
	file = (t_fl*)malloc(sizeof(t_fl));
	buf = file;
	while(get_next_line(fd, &tmp) > 0)
	{
		info->rooms += check_room(tmp);
		info->links += check_links(tmp);
		file->line = tmp;
		file->next = (t_fl*)malloc(sizeof(t_fl));
		file = file->next;
	}
	ft_strdel(&tmp);
	printf("rooms %d, links %d\n", info->rooms, info->links);
	printf("%s\n", buf->line);
	parsing(buf, info);
}