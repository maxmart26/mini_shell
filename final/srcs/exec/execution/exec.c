/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:34 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/08 14:08:28 by matorgue         ###   ########.fr       */
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

char	*ft_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
		i++;
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
	path_from_envp = ft_path(data->envp);
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
void	ft_dup2(t_data *data)
{
	int	i;

	i = 2;
	if (data->nb_pipe > 0)
	{
		printf(" le out %d et le in%d\n",data->fd_out,data->fd_in);
		ft_close_useless(data, data->nb_cmd, data->nb_cmd);
		if (data->fd_in > 2)
		{
			dup2(data->fd_in, STDIN_FILENO);
			close(data->fd_in);
		}
		if (data->fd_out > 2)
		{
			dup2(data->fd_out, STDOUT_FILENO);
			close(data->fd_out);
		}
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
void	exec(t_data *data, t_token *token)
{
	ft_exec(data, token);
	ft_dup2(data);
	//printf("data->path_def : %s\n\n  data->mycmdargs : %s\n\n",data->path_def, data->mycmdargs[0]);
	execve(data->path_def, data->mycmdargs, data->envp);
	printf("bash: %s: No such file or directory\n",data->mycmdargs[0]);
	free_tab(data->path);
	free_tab(data->mycmdargs);
	exit(127);
}
char	*ft_exec(t_data *data, t_token *token)
{
	int	i;

	i = 0;
//	printf("test\n");
	data->mycmdargs = ft_split(token->value, ' ');
	data->path_from_envp = ft_path(data->envp);
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
