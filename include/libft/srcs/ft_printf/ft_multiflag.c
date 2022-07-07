/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiflag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:01:34 by ncaba             #+#    #+#             */
/*   Updated: 2022/05/06 15:07:49 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

char	*brancher(int type, t_flags flags, va_list params, int *len)
{
	if (type == STRING)
		return (ft_convert_string(flags, params));
	if (type == POINTER)
		return (ft_convert_pointer(flags, params));
	if (type == INT)
		return (ft_convert_int(flags, params));
	if (type == HEX_UP)
		return (ft_convert_hexa(flags, params, TRUE));
	if (type == HEX_LOW)
		return (ft_convert_hexa(flags, params, FALSE));
	if (type == CHAR)
		return (ft_convert_char(flags, params, len));
	if (type == PERCENT)
		return (ft_convert_percent(flags));
	if (type == U_INT)
		return (ft_convert_unsigned(flags, params));
	return (NULL);
}

void	ft_decimal_check(char *str, t_flags *flags, int *loop, va_list params)
{
	int	nbr;

	str++;
	(*loop)++;
	if (*str == '*')
	{
		flags->nb_dec = va_arg(params, int);
		return ;
	}
	if (!ft_isdigit(*str))
	{
		flags->nb_dec = 0;
		(*loop)--;
		return ;
	}
	nbr = ft_atoi(str);
	while (ft_isdigit(*str))
	{
		(*loop)++;
		str++;
	}
	(*loop)--;
	flags->nb_dec = nbr;
}

void	ft_spacing_check(char *str, t_flags *flags, int *loop, va_list params)
{
	int	nbr;

	if (*str != '*')
	{
		nbr = ft_atoi(str);
		while (ft_isdigit(*str))
		{
			(*loop)++;
			str++;
		}
		(*loop)--;
		flags->nb_spaces = nbr;
	}
	else
		flags->nb_spaces = va_arg(params, int);
	if (flags->nb_spaces < 0)
	{
		flags->nb_spaces *= -1;
		flags->is_padded_left = 1;
		flags->is_padded_zero = FALSE;
	}
}

void	get_neg(long long *n, int *neg)
{
	if (*n < 0)
	{
		*neg = 1;
		*n *= -1;
	}
	else
		*neg = 0;
}
