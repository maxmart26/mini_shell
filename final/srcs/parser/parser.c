/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:42:44 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/06 16:47:38 by lnunez-t         ###   ########.fr       */
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
	t_token	*tmp;

	tmp = tools->lexer_list;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == GREAT || tmp->type == LESS
			|| tmp->type == HEREDOC || tmp->type == APPEND)
		{
			/*if (tmp->type == PIPE && tmp->next && (tmp->next->type == HEREDOC
					|| tmp->next->type == GREAT || tmp->next->type == LESS
					|| tmp->next->type == APPEND))
				tmp = tmp->next;*/
			if ((!tmp->prev && !tmp->next) || !tmp->next || (tmp->next
					&& tmp->next->type != WORD) || (tmp->type == PIPE
					&& !tmp->prev))
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

int	check_word_only(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (tmp->type == WORD && tmp->next->type == NEWL)
	{
		printf("%s", "bash: ");
		first_word(tmp->value);
		g_status = 258;
		return (printf(CMD_ERR), 1);
	}
	return (0);
}

int	check_null_list(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (!tmp && g_status != 6 && g_status != 5)
	{
		g_status = 258;
		return (1);
	}
	return (0);
}

int	check_dir(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (tmp && tmp->type == WORD && ft_strncmp(tmp->value, ".",
			ft_strlen(tmp->value)) == 0 && !tmp->next)
	{
		g_status = 258;
		ft_printf_error("bash: .: filename argument required\n");
		return (1);
	}
	else
		return (0);
}

void	parsing(t_data *tools)
{
	if (check_syntax(tools))
		return ;
	if (check_spe_char(tools))
		return ;
	if (check_null_list(tools))
		return ;
	if (check_dir(tools))
		return ;
}
