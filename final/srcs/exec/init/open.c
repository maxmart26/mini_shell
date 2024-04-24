/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:47:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/24 12:35:08 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

t_token	*new_token(t_token *token)
{
	while (token->prev)
	{
		if (token->prev->prev == NULL)
			break ;
		token = token->prev;
	}
	return (token);
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
			ft_printf_error("bash: %s: No such file or directory\n",
				token->next->value);
			if (data->nb_pipe == 0)
				exit(1);
		}
		tmp = token->next;
		token = tmp;
	}
}
