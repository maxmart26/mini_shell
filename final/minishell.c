/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:47:18 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/11 12:40:30 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

void	ft_tmp(t_data *data, t_token *token)
{
	pid_t	pid;
	t_token	*tmp;
	int		result;
	int		result2;

	result = -23;
	while (token)
	{
		if (token->type == CMD || token->type == CMD_BULT || token->type == CMD_ABS)
		{
			pid = fork();
			if (pid == 0)
			{
				redirection_builting(token, data);
			}
			data->nb_cmd++;
			waitpid(0, &result, 0);
			result2 = WEXITSTATUS(result);
			if (result2 == 155)
				ft_unset(token, data, -1);
			else if (result2 == 156)
				ft_export(token, data, -1);
			else if (result2 == 157)
				ft_cd(token, -1, data);
		}
		tmp = token->next;
		token = tmp;
	}
}

int	ft_main(t_data *data)
{
	open_fd(data, data->lexer_list);
	open_heredoc(data);
	if (data->std_int < 0 || data->std_out < 0)
		return (printf("probleme d"), 0);
	ft_tmp(data, data->lexer_list);
	if (data->std_out != 1)
		close(data->std_out);
	if (data->std_int != 0)
		close(data->std_int);
	return (0);
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
