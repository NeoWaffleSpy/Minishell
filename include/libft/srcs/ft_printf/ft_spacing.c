/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spacing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 04:11:51 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 12:32:21 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void	ft_add_space(char **str, t_flags flags, int type)
{
	char	*tmp;

	if (**str == '-' || type != INT)
		return ;
	if (flags.is_plus)
	{
		tmp = malloc_garbage(sizeof(char) * ft_strlen(*str) + 2);
		tmp[0] = '+';
		ft_strcpy(&(tmp[1]), *str);
		free_garbage(*str);
		*str = tmp;
		return ;
	}
	if (flags.is_single_space)
	{
		tmp = malloc_garbage(sizeof(char) * ft_strlen(*str) + 2);
		tmp[0] = ' ';
		ft_strcpy(&(tmp[1]), *str);
		free_garbage(*str);
		*str = tmp;
	}
}

static void	decalage(char **str, char *tmp, char x)
{
	tmp = malloc_garbage(sizeof(char) * ft_strlen(*str) + 3);
	tmp[0] = '0';
	tmp[1] = x;
	ft_strcpy(&(tmp[2]), *str);
	free_garbage(*str);
	*str = tmp;
}

void	ft_alternative(char **str, t_flags flags, int type)
{
	char	*tmp;
	char	x;

	tmp = *str;
	x = 'x';
	if (type == HEX_UP)
		x = 'X';
	if (flags.is_alternative || type == POINTER)
		if (type == HEX_UP || type == HEX_LOW || type == POINTER)
			decalage(str, tmp, x);
}

void	ft_add_precis(char **str, t_flags flags)
{
	char	padd;
	char	*tmp;

	padd = '0';
	if (**str == '-')
		flags.nb_dec++;
	while (flags.nb_dec > (int)ft_strlen(*str))
	{
		tmp = malloc_garbage(sizeof(char) * ft_strlen(*str) + 2);
		tmp[0] = padd;
		ft_strcpy(&(tmp[1]), *str);
		if (**str == '-')
		{
			tmp[1] = tmp[0];
			tmp[0] = **str;
		}
		free_garbage(*str);
		*str = tmp;
	}
}

void	ft_add_padd(char **str, t_flags flags, int type)
{
	char	padd;
	char	*tmp;

	padd = ' ';
	if (flags.is_padded_zero && type > 1 && type < 7)
		padd = '0';
	while (flags.nb_spaces > (int)ft_strlen(*str))
	{
		tmp = malloc_garbage(sizeof(char) * ft_strlen(*str) + 2);
		if (flags.is_padded_left)
		{
			ft_strcpy(tmp, *str);
			tmp[ft_strlen(*str)] = padd;
			tmp[ft_strlen(*str) + 1] = '\0';
		}
		else
		{
			tmp[0] = padd;
			ft_strcpy(&(tmp[1]), *str);
		}
		free_garbage(*str);
		*str = tmp;
	}
}
