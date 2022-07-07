/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 17:36:50 by ncaba             #+#    #+#             */
/*   Updated: 2022/05/06 13:23:54 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

static unsigned int	ft_strclen(char *save)
{
	unsigned int	i;

	i = 0;
	while (save && save[i] != '\n' && save[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strrejoin(char *s1, char *s2, size_t len)
{
	char			*str;
	int				nb;
	char			*tmp;

	nb = ft_strlen(s1) + ++len;
	str = (char *)ft_calloc(sizeof(char), nb + 1);
	tmp = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2 && --len > 0)
		*str++ = *s2++;
	*str = '\0';
	return (tmp);
}

static void	ft_chrandcpy(char **save)
{
	if (ft_strchr(*save, '\n'))
	{
		ft_strcpy(*save, ft_strchr(*save, '\n') + 1);
		return ;
	}
	free(*save);
	*save = NULL;
	return ;
}

static void	loopskip(char **point, int *res, char **save, int fd)
{
	if (!(ft_strchr(save[fd], '\n')))
		*res = read(fd, point[0], BUFFER_SIZE);
	point[0][*res] = '\0';
	point[1] = save[fd];
	save[fd] = ft_strrejoin(point[1], point[0], *res);
	free(point[1]);
}

int	get_next_line(int const fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*save[256];
	int				res;
	char			*point[2];

	point[0] = buff;
	res = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!(save[fd]))
		save[fd] = (char *)ft_calloc(1, 1);
	while (!(ft_strchr(save[fd], '\n') || res <= 0))
		loopskip(point, &res, save, fd);
	if (res < 0)
		return (-1);
	*line = ft_substr(save[fd], 0, ft_strclen(save[fd]));
	ft_chrandcpy(&save[fd]);
	if (res == 0)
		return (0);
	return (1);
}
