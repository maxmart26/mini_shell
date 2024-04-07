/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/06 02:46:01 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_free_env(t_env *env)
{
	t_env *tmp;

	while(env)
	{
		if (env->next)
			tmp = env->next;
		free(env->name);
		//free(env->value);
		//free(env->content);
		//free(env);
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
void	ft_exit(t_data *data,int i)
{
	if (i == 0)
		exit(158);
	else
	{
		if (data->std_int > 2)
			close (data->std_int);
		if (data->std_out > 2)
			close (data->std_out);
		ft_free_env(data->env);
		//free_tab(data->envp);
		if (data->nb_pipe > 0)
			ft_free_pipe(data->pipe_fd, data->nb_pipe);
		exit(1);
	}
}
