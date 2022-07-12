/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:08:33 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/12 17:36:45 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	ft_strlcpy_2(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	index;

	if (!src || !dst)
		return ;
	index = ft_strlen(src);
	if (index + 1 < size)
		size = index + 1;
	i = 0;
	while (i < size)
	{
		dst[i] = 0;
		dst[i] = src[i];
		i++;
	}
}

static void	ft_strlcat_2(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	index;

	if (!src || !dst)
		return ;
	index = ft_strlen(src);
	if (index + 1 < size)
		size = index + 1;
	j = ft_strlen(dst);
	i = 0;
	while (i < size)
	{
		dst[i + j] = src[i];
		i++;
	}
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(sizeof(char) * len + 1);
	ft_bzero(new_str, len + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy_2(new_str, s1, ft_strlen(s1));
	ft_strlcat_2(new_str, s2, ft_strlen(s2));
	return (new_str);
}
