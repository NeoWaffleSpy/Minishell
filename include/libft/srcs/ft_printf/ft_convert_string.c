/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:36:15 by ncaba             #+#    #+#             */
/*   Updated: 2022/05/06 14:50:42 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static void	dec_check(char *str, t_flags flags)
{
	int	loop;

	loop = ft_strlen(str) - 1;
	while (flags.nb_dec >= 0 && loop > (flags.nb_dec - 1))
	{
		str[loop] = '\0';
		loop--;
	}
}

char	*ft_convert_string(t_flags flags, va_list params)
{
	char	*result;

	result = ft_strdup(va_arg(params, char *));
	if (!result)
		result = ft_strdup("(null)");
	dec_check(result, flags);
	ft_add_padd(&result, flags, STRING);
	return (result);
}
