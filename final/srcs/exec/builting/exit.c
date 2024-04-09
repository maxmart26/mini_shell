/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:09:54 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/09 17:25:56 by matorgue         ###   ########.fr       */
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
		tmp = env->next;
		if (env->name != NULL)
			free(env->name);
		if (env->content != NULL)
			free(env->content);
		if (env->value != NULL)
			free(env->value);
		tmp = env->next;
		free(env);
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
	if (i == 0)
		exit(158);
	else
	{
		if (data->std_int > 2)
			close(data->std_int);
		if (data->std_out > 2)
			close(data->std_out);
		ft_free_env(data->env);
		if (data->nb_pipe > 0)
			ft_free_pipe(data->pipe_fd, data->nb_pipe);
		free(data);
		exit(1);
	}
}
