/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:20:17 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:41:23 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	index;
	char	*tmp;

	index = 0;
	tmp = NULL;
	while (index < n)
	{
		if (*((char *)s) == (char)c)
			return ((void *)s);
		s++;
		index++;
	}
	return (NULL);
}
