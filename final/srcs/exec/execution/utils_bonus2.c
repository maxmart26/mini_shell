/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:39:20 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/08 14:42:15 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_first_commande(t_data *data)
{
	int	i;

	i = 0;
	data->fd_in = data->std_int;
	data->fd_out = data->pipe_fd[0][1];
	printf("avec le out %d et le in %d first\n",data->fd_out, data->fd_in);
	while (i < data->nb_pipe)
	{
		if (i != 0)
			close(data->pipe_fd[i][1]);
		close(data->pipe_fd[i][0]);
		i++;
	}
}

void	ft_last_commande(t_data *data)
{
	int	i;

	i = 0;
	data->fd_in = data->pipe_fd[data->nb_pipe - 1][0];
	data->fd_out = data->std_out;
	printf("avec le out %d et le in %d last\n",data->fd_out, data->fd_in);
	while (i < data->nb_pipe)
	{
		close(data->pipe_fd[i][1]);
		if (i != data->nb_pipe - 1)
			close(data->pipe_fd[i][0]);
		i++;
	}
}

void	ft_middle_commande(t_data *data, int j)
{
	int	i;

	i = 0;
	printf("je suis nul\n");
	data->fd_out = data->pipe_fd[j][1];
	data->fd_in = data->pipe_fd[j - 1][0];
	printf("avec le out %d et le in %d\n",data->fd_out, data->fd_in);
	while (i < data->nb_pipe)
	{
		if (i != data->nb_cmd)
			close(data->pipe_fd[i][1]);
		if (i != data->nb_cmd - 1)
			close(data->pipe_fd[i][0]);
		i++;
	}
}

void	ft_close_useless(t_data *data, int i, int j)
{
	if (i == 0)
		ft_first_commande(data);
	else if (i == data->nb_pipe)
		ft_last_commande(data);
	else
		ft_middle_commande(data, j);
}
