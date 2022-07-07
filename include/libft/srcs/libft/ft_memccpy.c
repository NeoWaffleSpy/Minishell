/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:28:54 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:41:47 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			loop;
	unsigned char	*new_src;
	unsigned char	*new_dest;

	new_src = (unsigned char *)src;
	new_dest = (unsigned char *)dest;
	loop = 0;
	while (loop < n)
	{
		new_dest[loop] = new_src[loop];
		if (new_src[loop] == (unsigned char)c)
			return ((void *)&new_dest[loop + 1]);
		loop++;
	}
	return (NULL);
}
