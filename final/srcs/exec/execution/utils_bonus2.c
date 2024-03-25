/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:39:20 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/25 15:24:30 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_first_commande(t_data *data)
{
	int	i;

	i = 0;
	//close(data->std_out);
	data->fd_in = data->std_int;
	data->fd_out = data->pipe_fd[0][1];
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
	//close(data->std_int);
	printf("%d ici\n",data->pipe_fd[data->nb_pipe - 1][0]);
	data->fd_in = data->pipe_fd[data->nb_pipe - 1][0];
	data->fd_out = data->std_out;
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
	data->fd_out = data->pipe_fd[j][1];
	data->fd_in = data->pipe_fd[j - 1][0];
	close(data->std_out);
	close(data->std_int);
	while (i < data->nb_pipe)
	{
		if (i != j)
			close(data->pipe_fd[i][1]);
		if (i != j - 1)
			close(data->pipe_fd[i][0]);
		i++;
	}
}

void	ft_close_useless(t_data *data, int i, int j)
{
	//printf("%d et ici %d\n", i , j);
	if (i == 0)
		ft_first_commande(data);
	else if (i == data->nb_pipe)
		ft_last_commande(data);
	else
		ft_middle_commande(data, j);
}
