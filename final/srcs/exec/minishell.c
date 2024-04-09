/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:47:18 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/08 18:21:40 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void	fd_built(t_data *data, t_token *token)
{
	char	**str;

	str = ft_split(token->value, ' ');
	if (ft_strncmp(str[0], "echo", 4) == 0 && ft_strlen(str[0]) == 4)
		ft_echo(str);
	if (ft_strncmp(str[0], "pwd", 3) == 0 && ft_strlen(str[0]) == 3)
		ft_pwd(str);
	if (ft_strncmp(str[0], "env", 3) == 0 && ft_strlen(str[0]) == 3)
		ft_env(data);
	if (ft_strncmp(str[0], "cd", 2) == 0 && ft_strlen(str[0]) == 2)
		ft_cd(str, data->nb_pipe, data);
	if (ft_strncmp(str[0], "export", 6) == 0 && ft_strlen(str[0]) == 6)
		ft_export(str, data, data->nb_pipe);
	if (ft_strncmp(str[0], "exit", 4) == 0 && ft_strlen(str[0]) == 4)
		ft_exit(data, data->nb_pipe);
	if (ft_strncmp(str[0], "unset", 5) == 0 && ft_strlen(str[0]) == 5)
		ft_unset(str, data, data->nb_pipe);
}

void	after(t_data *data, t_token *token)
{
	fd_built(data, token);
	ft_exec_abs(token, data);
	exec(data, token);
}

void	ft_retry(t_data *data, int result, char **str)
{
	int	result2;

	result2 = WEXITSTATUS(result);
	if (result2 == 155)
		ft_unset(str, data, -1);
	else if (result2 == 156)
		ft_export(str, data, -1);
	else if (result2 == 157)
		ft_cd(str, -1, data);
	else if (result2 == 158)
	{
		free_tab(str);
		ft_exit(data, -1);
	}
}

int	ft_main(t_data *data)
{
	printf("test\n");
	ft_tmp(data, data->lexer_list);
	while (data->nb_pipe > 0)
	{
		free(data->pipe_fd[data->nb_pipe - 1]);
		data->nb_pipe--;
	}
	free(data->pipe_fd);
	return (0);
}
