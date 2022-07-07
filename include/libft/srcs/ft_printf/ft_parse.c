/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:56:09 by ncaba             #+#    #+#             */
/*   Updated: 2022/05/06 14:44:34 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static void	init_flags(t_flags *fl)
{
	fl->is_alternative = FALSE;
	fl->is_padded_zero = FALSE;
	fl->is_padded_left = FALSE;
	fl->is_single_space = FALSE;
	fl->is_plus = FALSE;
	fl->nb_spaces = 0;
	fl->nb_dec = -1;
}

static char	*return_percent(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (1 + 1));
	str[0] = '%';
	str[1] = '\0';
	return (str);
}

char	*ft_parse(char **str, va_list params, int *len)
{
	t_flags	flags;
	int		result;
	char	*str_result;

	init_flags(&flags);
	result = ft_grab_type(str, &flags, params);
	if (result == -1)
	{
		(*str)++;
		str_result = return_percent();
		return (str_result);
	}
	str_result = brancher(result, flags, params, len);
	return (str_result);
}

int	get_type(int *type, int p)
{
	*type = p;
	return (*type);
}

int	sort_letters(char c)
{
	if (c == 'u')
		return (U_INT);
	if (c == 's')
		return (STRING);
	if (c == 'p')
		return (POINTER);
	if (c == 'd' || c == 'i')
		return (INT);
	if (c == 'x')
		return (HEX_LOW);
	if (c == 'X')
		return (HEX_UP);
	if (c == 'c')
		return (CHAR);
	if (c == '%')
		return (PERCENT);
	return (0);
}
