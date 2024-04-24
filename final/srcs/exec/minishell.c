/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:47:18 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/24 14:36:07 by matorgue         ###   ########.fr       */
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

	fd = 0;
	if (i == 1)
		fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (i == 0)
		fd = open(s, O_RDONLY);
	return (fd);
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
	data->exit = result2;
	if (result2 == 155)
		ft_unset(str, data, -1);
	else if (result2 == 156)
		ft_export(str, data, -1);
	else if (result2 == 157)
		ft_cd(str, -1, data, 1);
	else if (result2 == 158)
	{
		ft_exit(data, -1, str);
	}
}

int	ft_main(t_data *data)
{
	ft_tmp(data, data->lexer_list);
	while (data->nb_pipe > 0)
	{
		free(data->pipe_fd[data->nb_pipe - 1]);
		data->nb_pipe--;
	}
	if (data->nb_pipe > 0)
		free(data->pipe_fd);
	return (0);
}
