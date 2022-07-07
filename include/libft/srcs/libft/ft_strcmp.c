/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:23:07 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:07:53 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while ((unsigned char)s1[index] == (unsigned char)s2[index]
		&& s1[index] && s2[index])
		index++;
	if ((unsigned char)s1[index] != (unsigned char)s2[index])
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	return (0);
}
