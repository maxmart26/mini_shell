/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:47:18 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/07 14:14:32 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void	new_token_after_fd(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;

	while (token->next != NULL)
	{
		if (token->type == GREAT || token->type == LESS)
		{
			tmp = token;
			tmp2 = token->next;
			token->prev->next = token->next->next;
			token->next->next->prev = token->prev;
			token = token->next->next;
			free(tmp);
			free(tmp2);
		}
		else
			token = token->next;
	}
	while (token != NULL)
		token = token->prev;
}

void	free_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_pipe)
	{
		free(data->pipe_fd[i]);
		i++;
	}
	free(data->pipe_fd);
}
int	open_file(char *s, int i)
{
	int	fd;

	fd = 0;
	if (i == 1)
		fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (i == 0)
		fd = open(s, O_RDONLY);
	return (fd);
}

void	open_fd(t_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	while (token)
	{
		if (token->type == GREAT)
		{
			if (data->std_out != 1)
			{
				close(data->std_out);
				data->std_out = 1;
			}
			data->std_out = open_file(token->next->value, 1);
		}
		else if (token->type == LESS)
			data->std_int = open_file(token->next->value, 0);
		if (data->std_int == -1 || data->std_out == -1)
		{
			printf("bash: %s: No such file or directory\n", token->next->value);
			if (data->nb_pipe == 0)
				exit(1);
		}
		tmp = token->next;
		token = tmp;
	}
}

void	fd_built(t_data *data, t_token *token)
{
	char	**str;

	str = ft_split(token->value, ' ');
	if (ft_strncmp(str[0], "echo", 4) == 0 && ft_strlen(str[0]) == 4)
		ft_echo(str);
	if (ft_strncmp(str[0], "pwd", 3) == 0 && ft_strlen(str[0]) == 3)
		ft_pwd(str);
	if (ft_strncmp(str[0], "env", 3) == 0 && ft_strlen(str[0]) == 3)
		ft_env(data);
	if (ft_strncmp(str[0], "cd", 2) == 0 && ft_strlen(str[0]) == 2)
		ft_cd(str, data->nb_pipe, data);
	if (ft_strncmp(str[0], "export", 6) == 0 && ft_strlen(str[0]) == 6)
		ft_export(str, data, data->nb_pipe);
	if (ft_strncmp(str[0], "exit", 4) == 0 && ft_strlen(str[0]) == 4)
		ft_exit(data, data->nb_pipe);
	if (ft_strncmp(str[0], "unset", 5) == 0 && ft_strlen(str[0]) == 5)
		ft_unset(str, data, data->nb_pipe);
}

void	after(t_data *data, t_token *token)
{
	fd_built(data, token);
	ft_exec_abs(token, data);
	exec(data, token);
}

void	ft_retry(t_data *data, int result, char **str)
{
	int	result2;

	result2 = WEXITSTATUS(result);
	if (result2 == 155)
		ft_unset(str, data, -1);
	else if (result2 == 156)
		ft_export(str, data, -1);
	else if (result2 == 157)
		ft_cd(str, -1, data);
	else if (result2 == 158)
	{
		free_tab(str);
		ft_exit(data, -1);
	}
}

void	ft_tmp(t_data *data, t_token *token)
{
	pid_t	pid;
	int		result;

	result = -23;
	while (token)
	{
		if (token->type == WORD)
		{
			pid = fork();
			if (pid == 0)
				after(data, token);
			data->nb_cmd++;
			wait(&result);
			ft_retry(data, result, ft_split(token->value, ' '));
		}
		token = token->next;
	}
}

int	ft_main(t_data *data)
{
	ft_tmp(data, data->lexer_list);
	return (0);
}
