/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:16:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/26 13:21:07 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	manage_no_pipe(t_data *data, t_token *token)
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

void	ft_dup2(t_data *data, t_token *token)
{
	int	i;

	i = 2;
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
	}
	else
		manage_no_pipe(data, token);
}
