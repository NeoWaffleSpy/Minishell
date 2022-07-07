/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:04:02 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:41:08 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			index;
	int				diff;
	unsigned char	*new_s1;
	unsigned char	*new_s2;

	index = 0;
	new_s1 = (unsigned char *)s1;
	new_s2 = (unsigned char *)s2;
	while (index < n)
	{
		diff = new_s1[index] - new_s2[index];
		if (diff != 0)
			return (diff);
		index++;
	}
	return (0);
}
