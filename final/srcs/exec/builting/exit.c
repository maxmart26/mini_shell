/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:09:54 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/19 12:17:25 by matorgue         ###   ########.fr       */
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

void	ft_exit(t_data *data, int i, char **str)
{
	if (i == 0)
	{
		ft_end(data, str);
		exit(158);
	}
	else
	{
		data->exit = ft_atoi(str[1]);
		if (data->exit < 0)
			data->exit = 156;
		ft_end(data, str);
		exit(data->exit);
	}
}
