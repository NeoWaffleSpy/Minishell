/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:54:52 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/05 21:31:27 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../include/minishell.h"

# include <stdio.h>

typedef struct s_pipex
{
	int		*pipefd;
	int		cmd_nbr;
	int		pipe_nbr;
	int		id;
	pid_t	pidn;
	char	*env_paths;
	char	**path_list;
	char	**cmd_arguments;
	char	*cmd;

}					t_pipex;
void	close_pipes(t_pipex *pipex, int except1, int except2);
/* FREE */
void	free_p_process(t_command var);
void	free_c_process(t_command *var, int fd1, int fd2);
/* CHILDS */
void	child(t_pipex *pipex, t_command *var, char *envp[]);
/* ERROR */
void	err_message(int fd, char *msg);
/* BUILT IN RELATED*/
void	selec_ope_pipex(t_var *main_process, t_command *var, t_pipex *pipex);
int		check_for_builtin(t_command *var);
#endif //PIPEX_H