/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:08:00 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/18 14:08:02 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

int main(int ac, char **av)
{
	t_inf	info;

	info.ants = 0;
	info.rooms = 0;
	info.room = NULL;
	info.links = 0;
	info.link = NULL;
	if(ac == 2)
	{
		read_map(av, &info);
		make_graph(&info);
	}
	else
		exit(0);
//	system("leaks lem-in");
	return (0);
}