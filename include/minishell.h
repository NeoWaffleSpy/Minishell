/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:51:13 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/12 22:55:41 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/include/ft_lib.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_var
{
	int		exit_loop;
	char	*current_dir;
}				t_var;

typedef struct s_command
{
	char				*command;
	char				*options;
	char				*arguments;
	struct s_command	*next;
}				t_command;

int		call_error(char *error, char *value);
void	call_info(char *info, char *value);
void	call_destroy(t_var *var, char *prompt);
void	free_command(t_command *comm);

int		selector(t_var *var, char *operation);

void	fill_command(t_command *comm, char *line);

#endif
