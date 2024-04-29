/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:48:54 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/29 15:47:19 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	close_fd_next(int i, int fd, t_token *token)
{
	if (i == 1)
	{
		if (token->fd_out > 2)
			close(token->fd_out);
		if (token->fd_out == -1)
		{
			close(fd);
			fd = -1;
		}
	}
}

t_token	*open_fd_great(t_token *token)
{
	int	fd;

	if (token->type == GREAT)
		fd = open_file(token->next->value, 1);
	else
		fd = open_file(token->next->value, 3);
	if (fd == -1)
	{
		ft_printf_error("bash: %s: No such file or directory\n",
			token->next->value);
	}
	token = new_token(token);
	if (!token)
		return (NULL);
	while (token->prev && token->prev->type != PIPE)
		token = token->prev;
	close_fd_next(1, fd, token);
	while (token && token->type != PIPE)
	{
		token->fd_out = fd;
		token = token->next;
	}
	return (token);
}

t_token	*open_fd_less(t_token *token)
{
	int	fd;

	fd = open_file(token->next->value, 0);
	if (fd == -1)
	{
		ft_printf_error("bash: %s: No such file or directory\n",
			token->next->value);
	}
	token = new_token(token);
	while (token->prev && token->prev->type != PIPE)
		token = token->prev;
	if (token->fd_int > 2)
		close(fd);
	if (token->fd_int == -1)
	{
		close(fd);
		fd = -1;
	}
	while (token && token->type != PIPE)
	{
		token->fd_int = fd;
		token = token->next;
	}
	return (token);
}

int	verif_type(t_token *token)
{
	if ((token->type == GREAT || token->type == LESS || token->type == HEREDOC
			|| token->type == APPEND))
		return (1);
	else
		return (0);
}

t_token	*open_fd_test(t_data *data)
{
	t_token *(result) = data->lexer_list;
	t_token *(tmp) = NULL;
	while (data->lexer_list->next)
	{
		if ((verif_type(data->lexer_list) == 1) && !data->lexer_list->prev)
			result = data->lexer_list->next->next;
		if (data->lexer_list->type == GREAT || data->lexer_list->type == APPEND)
			data->lexer_list = open_fd_great(data->lexer_list);
		else if (data->lexer_list->type == LESS)
			data->lexer_list = open_fd_less(data->lexer_list);
		else if (data->lexer_list->type == HEREDOC)
		{
			data->lexer_list = open_heredoc(data, data->lexer_list);
		}
		else if (data->lexer_list->next)
		{
			tmp = data->lexer_list->next;
			data->lexer_list = tmp;
		}
		if (!data->lexer_list || !data->lexer_list->next)
			break ;
	}
	return (result);
}
