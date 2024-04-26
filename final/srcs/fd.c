/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:41:42 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/26 12:42:54 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_include.h"
#include "../include/minishell_proto.h"
#include "../include/minishell_struct.h"

void	open_fd_great(t_token *token)
{
	int	fd;

	if (token->type == GREAT)
		fd = open_file(token->next->value, 1);
	else
		fd = open_file(token->next->value, 3);
	if (fd == -1)
		ft_printf_error("bash: %s: No such file or directory\n",
			token->next->value);
	token = new_token(token);
	while (token->prev && token->prev->type != PIPE)
		token = token->prev;
	if (token->fd_out > 2)
		close(fd);
	if (token->fd_out == -1)
	{
		close(fd);
		fd = -1;
	}
	while (token && token->type != PIPE)
	{
		token->fd_out = fd;
		token = token->next;
	}
}

void	open_fd_less(t_token *token)
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
}

t_token	*open_fd_test(t_data *data)
{
	t_token	*result;
	t_token	*tmp;

	result = data->lexer_list;
	while (data->lexer_list)
	{
		if ((data->lexer_list->type == GREAT || data->lexer_list->type == LESS)
			&& !data->lexer_list->next)
			result = data->lexer_list->next->next;
		if (data->lexer_list->type == GREAT || data->lexer_list->type == APPEND)
			open_fd_great(data->lexer_list);
		if (data->lexer_list->type == LESS)
			open_fd_less(data->lexer_list);
		if (!data->lexer_list->next)
			break ;
		tmp = data->lexer_list->next;
		data->lexer_list = tmp;
	}
	return (result);
}

void	init_fd(t_token *token)
{
	while (token)
	{
		token->fd_int = 0;
		token->fd_out = 1;
		token = token->next;
	}
}
