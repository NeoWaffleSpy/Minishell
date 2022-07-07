/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:17:12 by ncaba             #+#    #+#             */
/*   Updated: 2020/11/27 22:24:12 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	index;

	index = ft_strlen(src);
	if (!src)
		return (NULL);
	ft_memcpy(dst, src, index + 1);
	return (dst);
}
