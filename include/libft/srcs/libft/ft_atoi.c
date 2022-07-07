/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:45:17 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:02:35 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	rmspace(const char *nptr)
{
	t_boolean	is_space;
	int			counter;

	is_space = TRUE;
	counter = 0;
	while (is_space)
	{
		if (*nptr == ' ' || *nptr == '\n' || *nptr == '\v'
			|| *nptr == '\t' || *nptr == '\r' || *nptr == '\f')
		{
			nptr++;
			counter++;
		}
		else
			is_space = FALSE;
	}
	return (counter);
}

int	ft_atoi(const char *nptr)
{
	t_boolean	is_negative;
	int			result;

	is_negative = FALSE;
	result = 0;
	nptr += rmspace(nptr);
	if (ft_strncmp(nptr, "-2147483648", 12) == 0)
		return (-2147483648);
	if (*nptr == '-')
	{
		nptr++;
		is_negative = TRUE;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		if (result * 10 + (int)(*nptr - '0') < result)
			return (is_negative - 1);
		result = result * 10 + (int)(*nptr - '0');
		nptr++;
	}
	if (is_negative)
		result *= -1;
	return (result);
}
