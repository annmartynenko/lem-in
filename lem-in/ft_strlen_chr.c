/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:50:50 by amartyne          #+#    #+#             */
/*   Updated: 2019/01/11 14:50:51 by amartyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

size_t	ft_strlen_chr(const char *s, int c)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	if (s == NULL || s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			len++;
		i++;
	}
	return (len);
}
