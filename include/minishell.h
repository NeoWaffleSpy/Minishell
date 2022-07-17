/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:51:13 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/17 19:49:52 by ncaba            ###   ########.fr       */
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

typedef struct s_env
{
	char				*name;
	char				*content;
	struct s_env		*next;
}				t_env;

typedef struct s_var
{
	int					exit_loop;
	char				*current_dir;
	t_env				*env;
	int					quotes;
	int					dquotes;
}				t_var;

typedef struct s_command
{
	char				*command;
	char				*options;
	char				*arguments;
	char				*infile;
	char				*outfile;
	struct s_command	*next;
}				t_command;

int			call_error(char *error, char *value);
void		call_info(char *info, char *value);
void		call_destroy(t_var *var, char *prompt);
void		free_command(t_command **comm);

int			selector(t_var *var, char *operation);

t_command	*fill_command(char *line);

/* UTILS */

void		clean_str(char **old);
char		*multiline_quotes(char *line, t_var *var);
void		count_quotes(char *line, t_var *var);

/* BUILTINS */

/* ENV */

t_env		*ft_env_last(t_env *env);
void		ft_env_add_back(t_env **env_start, t_env *new);
t_env		*ft_get_env_element(t_env *env, char *env_line);
void		ft_delone_env(t_env *env);
void		ft_cleanly_delone_env(t_env **env_start, t_env *target);
int			ft_print_env(t_env *env_list, char *arg, char *options);
char		**ft_env_to_char(t_env *env);
t_env		*ft_env_to_list(char **env);
int			ft_env_size(t_env *env);
int			ft_is_valid_env_variable(char *str);
void		ft_free_env(t_env *env_start);
void		ft_deal_with_existing_env_var(t_env **env_list, t_env *to_add);
void		ft_manually_add_one_env(t_env *env_list, char *name, char *content);
t_env		*ft_find_env_elem(t_env *env_list, char *name);

#endif
