/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:16:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/10 10:30:53 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_dup2_next(t_data *data, t_token *token)
{
	if (token->fd_int != 0)
		data->std_int = token->fd_int;
	if (token->fd_out != 1)
		data->std_out = token->fd_out;
	dup2(data->std_int, STDIN_FILENO);
	dup2(data->std_out, STDOUT_FILENO);
	if (data->std_int > 2)
		close(data->std_int);
	if (data->std_out > 2)
		close(data->std_out);
}

void	ft_end_dup(t_token *token)
{
	while (token->prev)
		token = token->prev;
	while (token)
	{
		if (token->fd_int > 2)
			close(token->fd_int);
		if (token->fd_out > 2)
			close(token->fd_out);
		token = token->next;
	}
}

void	ft_dup2(t_data *data, t_token *token)
{
	int (i) = 0;
	if (data->nb_pipe > 0)
	{
		ft_close_useless(data, data->nb_cmd, data->nb_cmd);
		if (token->fd_int != 0)
			data->fd_in = token->fd_int;
		if (token->fd_out != 1)
			data->fd_out = token->fd_out;
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		if (data->fd_in > 2)
			close(data->fd_in);
		if (data->fd_out > 2)
			close(data->fd_out);
		while (i < data->nb_pipe)
		{
			close(data->pipe_fd[i][0]);
			close(data->pipe_fd[i][1]);
			i++;
		}
	}
	else
		ft_dup2_next(data, token);
	ft_end_dup(token);
}
