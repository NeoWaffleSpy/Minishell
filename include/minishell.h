/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:51:13 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/05 16:17:32 by ncaba            ###   ########.fr       */
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
# include <errno.h>
# include <signal.h>

typedef struct s_env
{
	char				*name;
	char				*content;
	struct s_env		*next;
}				t_env;

typedef struct s_var
{
	int					exit_loop;
	t_env				*env;
	int					quotes;
	int					dquotes;
	int					exit_status;
}				t_var;

typedef struct s_file
{
	char			*filename;
	int				is_append;
	struct s_file	*next;
}				t_file;

typedef struct s_command
{
	char				*command;
	t_list				*options;
	t_list				*arguments;
	t_file				*infile;
	t_file				*outfile;
	int					infile_fd;
	int					outfile_fd;
	int					error;
	t_file				*delim;
	struct s_command	*next;
}				t_command;

int			call_error(char *error, char *value, int ret);
void		call_info(char *info, char *value);
void		call_todo(char *ft);
void		call_destroy(t_var *var, char *prompt);
void		free_command(t_command *comm);

int			selector(t_var *var, char *operation);

t_command	*fill_command(char *line);

/* UTILS */

char		*clean_str(char *old);
char		*multiline_quotes(char *line, t_var *var);
void		count_quotes(char *line, t_var *var);
char		*ft_buffalloc(char *str, char c);
void		cpy_str(char **dst, char *src);
t_command	*init_comm(void);
void		init_signal(void);
void		init_heredoc(int *return_value);
void		init_child(void);
void		init_var(t_var *var, t_env *env);
void		reset_var(t_var *var);
void		refresh_handler(int sig);
void		heredoc_handler(int sig);
char		**split_command(char *str);
void		replace_tilde(char **tmp, char **res, int pos);
void		create_heredoc(t_var *var, t_file *delim);
void		sigint_handler(int	*return_value);
int			ft_lstfadd_front(t_file **alst, t_file *new);
int			ft_lstfadd_back(t_file **alst, t_file *new);
void		ft_lstfclear(t_file **lst, void (*del)(void*));
t_file		*ft_lstfnew(void *content, int append);

/* BUILTINS */

void		print_pwd(t_var *var, t_command *comm);
void		replace_dollar(t_var *var, char **replace, int is_only_var);
void		ft_echo(t_command *comm);
void		export_var(t_var *var, t_command *comm);
void		cd(t_var *var, t_command *comm);
void		unset_var(t_var *var, t_command *comm);
int			check_valid_name(t_var *var, char *str);
void		exit_mini(t_var *var, t_command *comm);

/* ENV */

t_env		*ft_env_last(t_env *env);
void		ft_env_add_back(t_env **env_start, t_env *new);
t_env		*ft_get_env_element(t_env *env, char *env_line);
void		ft_delone_env(t_env *env);
void		ft_cleanly_delone_env(t_env **env_start, t_env *target);
int			ft_print_env(t_env *env_list, t_command *comm);
char		**ft_env_to_char(t_env *env);
t_env		*ft_env_to_list(char **env);
int			ft_env_size(t_env *env);
int			ft_is_valid_env_variable(char *str);
void		ft_free_env(t_env *env_start);
void		ft_deal_with_existing_env_var(t_env **env_list, t_env *to_add);
void		ft_manually_add_one_env(t_env *env_list, char *name, char *content);
t_env		*ft_find_env_elem(t_env *env_list, char *name);

/* A BOUGER */

int			check_valid_path(char *path);

#endif
