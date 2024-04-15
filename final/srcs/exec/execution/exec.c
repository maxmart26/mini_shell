/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:34 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/15 17:28:55 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_free_tab(char **input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
}

char	*ft_path(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->value, "PATH=", 5) == 0)
		{
			return (&env->value[5]);
		}
		env = env->next;
	}
	return (NULL);
}

char	*get_path(t_data *data, t_token *token)
{
	char	*path_from_envp;
	char	**path;
	char	*path_def;
	int		i;

	i = 0;
	if (data == NULL)
	{
		return (NULL);
	}
	path_from_envp = ft_path(data->env);
	path = ft_split(path_from_envp, ':');
	while (path[i])
	{
		path_from_envp = ft_strjoin(path[i], "/");
		path_def = ft_strjoin(path_from_envp, token->value);
		free(path_from_envp);
		if (access(path_def, 0) == 0)
			return (path_def);
		else
			free(path_def);
		i++;
	}
	ft_free_tab(path);
	return (NULL);
}

void	exec(t_data *data, t_token *token)
{
	ft_exec(data, token);
	ft_dup2(data);
	execve(data->path_def, data->mycmdargs, data->envp);
	ft_printf_error("bash: %s: commande not found\n", data->mycmdargs[0]);
	free_tab(data->path);
	free_tab(data->mycmdargs);
	exit(127);
}

char	*ft_exec(t_data *data, t_token *token)
{
	int	i;

	i = 0;
	data->mycmdargs = ft_split(token->value, ' ');
	if ((data->path_from_envp = ft_path(data->env)) == NULL
		&& data->r_path == TRUE)
		return (exec_path(data));
	else if ((data->path_from_envp = ft_path(data->env)) == NULL
		&& data->r_path == FALSE)
		return (perror(CMD_ERR), NULL);
	data->path = ft_split(data->path_from_envp, ':');
	while (data->path[i])
	{
		data->path_temp = ft_strjoin(data->path[i], "/");
		data->path_def = ft_strjoin(data->path_temp, data->mycmdargs[0]);
		free(data->path_temp);
		if (access(data->path_def, 0) == 0)
			return (data->path_def);
		else
		{
			free(data->path_def);
		}
		i++;
	}
	return (NULL);
}
