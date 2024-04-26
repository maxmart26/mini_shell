/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:00:02 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/26 13:17:57 by lnunez-t         ###   ########.fr       */
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

void	ft_tmp_close(t_data *data, t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->fd_int > 2)
			close(token->fd_int);
		if (token->fd_out > 2)
			close(token->fd_out);
		token = token->next;
	}
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
	int		i;
	char	**str;

	str = NULL;
	ft_tmp_close(data, token);
	i = 0;
	while (token)
	{
		if (token->type == WORD)
		{
			waitpid(pid[i], &result, 0);
			str = ft_split(token->value, ' ');
			ft_retry(data, result, str, token);
			ft_free_tab(str);
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
	int	result;

	data->nb_com = ft_cmd(token);
	result = -23;
	data->pid = malloc(data->nb_com * sizeof(pid_t));
	if (!data->pid)
		return ;
	data->nb_com = 0;
	while (token)
	{
		if (token->type == WORD)
		{
			data->pid[data->nb_com] = fork();
			if (data->pid[data->nb_com] == 0)
				after(data, token);
			data->nb_cmd++;
			data->nb_com++;
		}
		token = token->next;
	}
	token = data->lexer_list;
	ft_tmp2(data, token, result, data->pid);
}
