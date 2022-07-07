/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:51:13 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/07 18:17:54 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/include/ft_lib.h"
# include <./readline/libreadline.a>
# include <./readline/libhistory.a>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int		call_error(char *error, char *value);
void	call_info(char *info, char *value);

#endif
