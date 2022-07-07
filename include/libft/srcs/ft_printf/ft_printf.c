/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:54:57 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 12:32:43 by ncaba            ###   ########.fr       */
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
