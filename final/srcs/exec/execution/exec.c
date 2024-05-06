/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:34 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/06 14:22:01 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

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
	path = NULL;
	if (data == NULL)
		return (NULL);
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

void	exec_no_acc(t_data *data)
{
	ft_printf_error(" Is a directory\n");
	free_tab(data->path);
	destroy_token_list(data->lexer_list);
	ft_destroy_env(data->env);
	while (data->nb_pipe >= 1)
	{
		free(data->pipe_fd[data->nb_pipe - 1]);
		if (data->nb_pipe == 1)
			break ;
		data->nb_pipe--;
	}
	if (data->nb_pipe > 0)
		free(data->pipe_fd);
	free(data->pid);
	free(data);
	exit(126);
}

void	exec(t_data *data, t_token *token)
{
	if (ft_exec(data, token) != NULL)
	{
		ft_dup2(data, token);
		execve(data->path_def, data->mycmdargs, data->envp);
	}
	if (access(data->mycmdargs[0], 0) == 0)
		exec_no_acc(data);
	ft_printf_error("bash: %s: command not found\n", data->mycmdargs[0]);
	ft_destroy_env(data->env);
	ft_tmp_close(data, token);
	free(data->pid);
	if (data->path != NULL)
		free_tab(data->path);
	destroy_token_list(data->lexer_list);
	while (data->nb_pipe >= 1)
	{
		free(data->pipe_fd[data->nb_pipe - 1]);
		if (data->nb_pipe == 1)
			break ;
		data->nb_pipe--;
	}
	if (data->nb_pipe > 0)
		free(data->pipe_fd);
	free(data);
	exit(127);
}

char	*ft_exec(t_data *data, t_token *token)
{
	int	i;

	i = 0;
	data->mycmdargs = token->str;
	data->path_from_envp = ft_path(data->env);
	if (data->path_from_envp == NULL && data->r_path == TRUE)
		return (exec_path(data));
	else if (data->path_from_envp == NULL && data->r_path == FALSE)
	{
		data->path = NULL;
		return (NULL);
	}
	data->path = ft_split(data->path_from_envp, ':');
	while (data->path[i])
	{
		data->path_temp = ft_strjoin(data->path[i], "/");
		data->path_def = ft_strjoin(data->path_temp, data->mycmdargs[0]);
		free(data->path_temp);
		if (access(data->path_def, 0) == 0)
			return (data->path_def);
		else
			free(data->path_def);
		i++;
	}
	return (NULL);
}
