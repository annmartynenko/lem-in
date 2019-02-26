/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:58:58 by amartyne          #+#    #+#             */
/*   Updated: 2019/02/26 19:58:59 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

char **create_color()
{
	char **color;

	color = (char**)malloc(sizeof(char*) * 12);
	color[0] = "\033[0;31m";
	color[1] = "\033[1;31m";
	color[2] = "\033[0;32m";
	color[3] = "\033[1;32m";
	color[4] = "\033[0;33m";
	color[5] = "\033[01;33m";
	color[6] = "\033[0;34m";
	color[7] = "\033[1;34m";
	color[8] = "\033[0;35m";
	color[9] = "\033[1;35m";
	color[10] = "\033[0;36m";
	color[11] = "\033[1;36m";
	return (color);
}