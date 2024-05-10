/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:42:44 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/10 13:29:08 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	check_spe_char(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->value && strncmp(tmp->value, "&", 1) == 0)
		{
			printf(SYNTAX_ERR);
			g_status = 258;
			return (printf("%s'\n", "&&"), 1);
		}
		else if (tmp->type == SEMI)
		{
			printf(SYNTAX_ERR);
			g_status = 258;
			return (printf("%s'\n", ";"), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	print_error_message(int type)
{
	if (type == 0)
		return ;
	else if (type == 1)
	{
		ft_printf_error("bash: syntax error near unexpected token `>'\n");
		return ;
	}
	else if (type == 2)
	{
		ft_printf_error("bash: syntax error near unexpected token `<'\n");
		return ;
	}
	else if (type == 3)
	{
		ft_printf_error("bash: syntax error near unexpected token `<<'\n");
		return ;
	}
	else if (type == 4)
	{
		ft_printf_error("bash: syntax error near unexpected token `>>'\n");
		return ;
	}
	else
		return ;
}

void	ft_free_pipe_fd(t_data *data)
{
	while (data->nb_pipe >= 1)
	{
		free(data->pipe_fd[data->nb_pipe - 1]);
		if (data->nb_pipe == 1)
			break ;
		data->nb_pipe--;
	}
	if (data->nb_pipe > 0)
		free(data->pipe_fd);
}

void	print_error(t_token *token, t_data *tools)
{
	t_token	*tmp;
	int		type;

	type = 0;
	tmp = tools->lexer_list;
	count_pipes(tmp, tools);
	if (tools->nb_pipe > 0)
	{
		ft_printf_error("bash: syntax error near unexpected token `|'\n");
		return ;
	}
	while (token)
	{
		if (token->type == GREAT)
			type = 1;
		else if (token->type == LESS)
			type = 2;
		else if (token->type == HEREDOC)
			type = 3;
		else if (token->type == APPEND)
			type = 4;
		token = token->next;
	}
	print_error_message(type);
}

int	check_pipe(t_data *tools)
{
	t_token *(tmp) = tools->lexer_list;
	while (tmp)
	{
		if (first_check(tmp))
			return (1);
		if (tmp->type == PIPE || tmp->type == GREAT || tmp->type == LESS
			|| tmp->type == HEREDOC || tmp->type == APPEND)
		{
			if ((!tmp->prev && !tmp->next) || !tmp->next || (tmp->next
					&& tmp->next->type == PIPE) || (tmp->type == PIPE
					&& !tmp->prev) || (tmp->type == PIPE && (tmp->type == GREAT
						|| tmp->type == LESS || tmp->type == HEREDOC
						|| tmp->type == APPEND) && !tmp->next->next))
			{
				print_error(tmp, tools);
				g_status = 258;
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
