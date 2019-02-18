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

int 	check_room(char *tmp)
{
	int i;
	int sp;

	i = 1;
	sp = 0;
	if(tmp[0] == '#')
		return(0);
	else if(tmp[0] == 'L')
		exit_l("forbidden char L");
	while (tmp[i])
	{
		if (tmp[i] != ' ' && (sp == 1 || sp == 2) && !ft_isdigit(tmp[i]))
			exit_l("not valid coordinates");
		if (tmp[i] == ' ')
			sp++;
		if	(tmp[i] == '-')
			return (0);
		if (sp > 3)
			exit_l("too much spaces");
		i++;
	}
	if (sp == 2)
		return (1);
//	ft_strdel(&tmp);
	return (0);
}

void	check_ants(int fd, t_inf *info)
{
	char *tmp;
	int i;

	i= 0;
	get_next_line(fd, &tmp);
	if (!(info->ants = ft_atoi(tmp)))
		exit_l("no count of ants");
	if (info->ants < 1 || info->ants >= 2147483647)
		exit_l("number of ants is less than 1 or more than INT_MAX");
	while(tmp[i] && ft_isdigit(tmp[i]))
		i++;
	if (tmp[i] != '\0')
		exit_l("no count of ants");
	ft_strdel(&tmp);
}

int 	check_links(char *tmp)
{
	int i;
	int hyphen;

	i = 0;
	hyphen = 0;
	if (tmp[0] == '#')
		return (0);
	while (tmp[i])
	{
		if (tmp[i] == ' ')
			return (0);
		if (tmp[i] == '-')
			hyphen++;
		if (hyphen > 1)
			exit_l("too much hyphen");
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
	file->next = NULL;
	buf = file;
	while(get_next_line(fd, &tmp))
	{
		info->rooms += check_room(tmp);
		info->links += check_links(tmp);
		file->line = ft_strdup(tmp);
//		printf("tmp %s, file %s\n", tmp, file->line);
		file->next = (t_fl*)malloc(sizeof(t_fl));
		file = file->next;
		file->next = NULL;
		ft_strdel(&tmp);
	}
	if (info->links < 1)
		exit_l("less than 1 link in the map");
//	free(file);
	file->next = NULL;
	ft_strdel(&tmp);
	printf("ants %d\n", info->ants);
	printf("rooms %d, links %d\n", info->rooms, info->links);
//	printf("%s\n", buf->line);
	parsing(buf, info);
	while (buf)
	{
		file = buf->next;
		if (buf->next)
			free(buf->line);
		free(buf);
		buf = file;
	}
//	printf("%d, %d\n", info->ants, info->link[1].rm1);
}