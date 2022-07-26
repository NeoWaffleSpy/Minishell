/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:45:58 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:03:52 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static t_boolean	is_ref(char c, const char *ref)
{
	while (*ref)
	{
		if (c == *ref)
		{
			return (TRUE);
		}
		ref++;
	}
	return (FALSE);
}

static void	*return_null(void)
{
	void	*s;

	s = malloc_garbage(sizeof(char));
	if (!s)
		return (NULL);
	*(char *)s = '\0';
	return (s);
}

char	*ft_strtrim(const char *s1, const char *ref)
{
	int		endroit;
	int		envers;

	if (!s1)
		return (NULL);
	if (!ref)
		return (ft_strdup(s1));
	endroit = 0;
	envers = ft_strlen(s1) - 1;
	while (is_ref(s1[endroit], ref))
		endroit++;
	if (!s1[endroit])
		return ((char *)return_null());
	while (is_ref(s1[envers], ref))
		envers--;
	return (ft_substr(s1, endroit, envers - endroit + 1));
}
