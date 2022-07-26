/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 17:37:12 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/26 20:38:49 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define TRUE 1
# define FALSE 0
# define MAXINT 2147483647
# define MININT -2147483648
# define BUFFER_SIZE 255
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

int		get_next_line(int const fd, char **line);

#endif
