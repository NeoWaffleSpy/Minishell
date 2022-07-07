/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:46:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/07 17:07:04 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*create_prompt()
{
	char	*prompt;

	prompt = ft_strdup("[test_prompt]->");
}

static void	read_command(char *prompt)
{
	char	*line;

	line = readline(prompt);
	call_info("Line read:", line);
	free(line);
}

int	main(void)
{
	char	*prompt;

	prompt = create_prompt();
	read_command(prompt);
	free(prompt);
}
