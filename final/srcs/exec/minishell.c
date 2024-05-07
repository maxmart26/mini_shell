/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:47:18 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/07 18:07:09 by lnunez-t         ###   ########.fr       */
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

void	free_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_pipe)
	{
		free(data->pipe_fd[i]);
		i++;
	}
	free(data->pipe_fd);
}

int	open_file(char *s, int i)
{
	int	fd;

	if (i == 1)
		fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (i == 0)
		fd = open(s, O_RDONLY);
	else
		fd = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	return (fd);
}

void	after(t_data *data, t_token *token)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (token->fd_int == -1 || token->fd_out == -1 || !token->value)
	{
		if (!token->value)
			printf("%s\n", "bash: command not found");
		ft_destroy_env(data->env);
		destroy_token_list(data->lexer_list);
		while (data->nb_pipe >= 1)
		{
			free(data->pipe_fd[data->nb_pipe - 1]);
			if (data->nb_pipe == 1)
				break ;
			data->nb_pipe--;
		}
		if (data->nb_pipe > 0)
			free(data->pipe_fd);
		free(data->pid);
		free(data);
		exit(1);
	}
	fd_built(data, token);
	ft_exec_abs(token, data);
	exec(data, token);
}

void	ft_retry(t_data *data, int result, char **str, t_token *token)
{
	int	result2;

	result2 = WEXITSTATUS(result);
	data->exit = result2;
	if (result2 == 155)
		ft_unset(str, data, -1);
	else if (result2 == 199)
		ft_export(str, data, -1, token);
	else if (result2 == 157)
		ft_cd(str, -1, data, token);
	else if (result2 == 158)
	{
		ft_exit(data, -1, str);
	}
}

int	ft_main(t_data *data)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	g_status = 2;
	ft_tmp(data, data->lexer_list);
	while (data->nb_pipe >= 1)
	{
		free(data->pipe_fd[data->nb_pipe - 1]);
		if (data->nb_pipe == 1)
			break ;
		data->nb_pipe--;
	}
	if (data->nb_pipe > 0)
		free(data->pipe_fd);
	free(data->pid);
	destroy_token_list(data->lexer_list);
	g_status = 1;
	return (0);
}
