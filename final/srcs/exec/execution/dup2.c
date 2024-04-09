/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:16:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/08 16:17:01 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_dup2(t_data *data)
{
	int	i;

	i = 2;
	if (data->nb_pipe > 0)
	{
		ft_close_useless(data, data->nb_cmd, data->nb_cmd);
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		if (data->fd_in > 2)
			close(data->fd_in);
		if (data->fd_out > 2)
			close(data->fd_out);
	}
	else
	{
		dup2(data->std_int, STDIN_FILENO);
		dup2(data->std_out, STDOUT_FILENO);
		if (data->std_int > 2)
			close(data->std_int);
		if (data->std_out > 2)
			close(data->std_out);
	}
}
