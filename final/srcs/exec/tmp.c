/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:00:02 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/08 16:04:50 by matorgue         ###   ########.fr       */
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

void	ft_tmp_close(t_data *data)
{
	int	i;

	i = 0;
	if (data->std_int > 2)
		close(data->std_int);
	if (data->std_out > 2)
		close(data->std_out);
	if (data->nb_pipe > 0)
	{
		while (i < data->nb_pipe)
		{
			close(data->pipe_fd[i][0]);
			close(data->pipe_fd[i][1]);
			i++;
		}
	}
}

void	ft_tmp2(t_data *data, t_token *token, int result, pid_t *pid)
{
	int	i;

	ft_tmp_close(data);
	i = 0;
	while (token)
	{
		if (token->type == WORD)
		{
			waitpid(pid[i], &result, 0);
			ft_retry(data, result, ft_split(token->value, ' '));
			i++;
		}
		token = token->next;
	}
}

int	ft_cmd(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == WORD)
			i++;
		token = token->next;
	}
	return (i);
}

void	ft_tmp(t_data *data, t_token *token)
{
	pid_t	*pid;
	int		result;
	int		i;

	i = ft_cmd(token);
	result = -23;
	pid = malloc(i * sizeof(pid_t));
	i = 0;
	while (token)
	{
		if (token->type == WORD)
		{
			pid[i] = fork();
			if (pid[i] == 0)
				after(data, token);
			data->nb_cmd++;
			i++;
		}
		token = token->next;
	}
	token = data->lexer_list;
	ft_tmp2(data, token, result, pid);
}