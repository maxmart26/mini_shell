/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:09:54 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/10 15:43:04 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		if (env->next)
			tmp = env->next;
		free(env->name);
		env = tmp;
	}
}

void	ft_free_pipe(int **fd, int i)
{
	while (i > 0)
	{
		free(fd[i - 1]);
		i--;
	}
	free(fd);
}

void	ft_exit(t_data *data, int i)
{
	(void)data;
	if (i == 0)
		exit(158);
	else
	{
		/*if (data->std_int > 2)
			close(data->std_int);
		if (data->std_out > 2)
			close(data->std_out);
		if (data->nb_pipe > 0)
			ft_free_pipe(data->pipe_fd, data->nb_pipe);*/
		free_minishell_ctrld(data);
		exit(1);
	}
}
