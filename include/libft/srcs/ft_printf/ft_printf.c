/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:54:57 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/12 17:37:21 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static int	putstr_free(char *str, int fd)
{
	int	len;

	len = 0;
	len = (int)ft_strlen(str);
	ft_putstr_fd(str, fd);
	free(str);
	return (len);
}

int	ft_printf(char *str, ...)
{
	va_list	params;
	int		result;

	result = 0;
	va_start(params, str);
	while (*str)
	{
		while (*str && *str != '%')
		{
			ft_putchar(*str);
			str++;
			result++;
		}
		if (*str)
			result += putstr_free(ft_parse(&str, params, &result), 1);
	}
	va_end(params);
	return (result);
}

int	ft_printf_fd(int fd, char *str, ...)
{
	va_list	params;
	int		result;

	result = 0;
	va_start(params, str);
	while (*str)
	{
		while (*str && *str != '%')
		{
			ft_putchar_fd(*str, fd);
			str++;
			result++;
		}
		if (*str)
			result += putstr_free(ft_parse(&str, params, &result), fd);
	}
	va_end(params);
	return (result);
}

void	better_join(char **line, char **source)
{
	char	*tmp;

	tmp = ft_strjoin(*line, *source);
	free(*source);
	free(*line);
	*line = tmp;
}

char	*ft_printf_var(char *str, ...)
{
	va_list	params;
	int		result;
	char	*line;
	char	*tmp;

	line = NULL;
	va_start(params, str);
	while (*str)
	{
		result = 0;
		while (str[result] && str[result] != '%')
			result++;
		tmp = ft_substr(str, 0, result);
		better_join(&line, &tmp);
		str += result;
		if (*str)
		{
			tmp = ft_parse(&str, params, &result);
			better_join(&line, &tmp);
		}
	}
	va_end(params);
	return (line);
}
