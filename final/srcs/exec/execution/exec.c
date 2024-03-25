/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:34 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/25 15:24:25 by lnunez-t         ###   ########.fr       */
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
	if (data->nb_pipe > 0)
	{
		printf("avant %d et %d\n", data->fd_in, data->fd_out);
		ft_close_useless(data, data->nb_cmd, data->nb_cmd);
		printf(" apres %d et %d\n", data->fd_in, data->fd_out);
		dup2(data->fd_out, STDOUT_FILENO);
		dup2(data->fd_in, STDIN_FILENO);
	}
	else
	{
		dup2(data->std_int, STDIN_FILENO);
		dup2(data->std_out, STDOUT_FILENO);
	}
}
void	ft_exec(t_data *data, t_token *token)
{
	char	*path_def;
	char	*tmp;
	char	**mycmdargs;
	char	*tmp2;
	int		i;

	i = 0;
	if (token->next != NULL && token->next->type == OPT)
	{
		path_def = ft_strjoin(token->value, " ");
		tmp = ft_strjoin(path_def, token->next->value);
		mycmdargs = ft_split(tmp, ' ');
		free(path_def);
		free(tmp);
		path_def = get_path(data, token);
	}
	else
	{
		if (token->next->type == ARG)
		{
			path_def = ft_strjoin(token->value, " ");
			tmp = ft_strjoin(path_def, token->next->value);
			while (token->next->next->type == ARG)
			{
				tmp2 = tmp;
				path_def = ft_strjoin(tmp, " ");
				tmp = ft_strjoin(path_def, token->next->next->value);

				free(tmp2);
				free(path_def);
				token = token->next;
				i++;
			}
			while (i > 0)
			{
				token = token->prev;
				i--;
			}
		}
		else
			tmp = token->value;
		mycmdargs = ft_split(tmp, ' ');
		path_def = get_path(data, token);
	}
	if (!path_def)
	{
		printf("%s: command not found\n", token->value);
		close(data->std_int);
		close(data->std_out);
		exit(1);
	}
	ft_dup2(data);
	execve(path_def, mycmdargs, data->envp);
	exit(0);
}
