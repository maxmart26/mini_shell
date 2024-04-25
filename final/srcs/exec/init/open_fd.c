/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:28:38 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/24 15:39:02 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	open_fd2(t_data *data, t_token *token)
{
	if (!token->next)
	{
		printf(SYNTAX_ERR "%s'\n", "newline");
		g_status = 258;
		return ;
	}
	if (data->std_out != 1)
	{
		close(data->std_out);
		data->std_out = 1;
	}
	data->std_out = open_file(token->next->value, 1);
}

void	open_fd(t_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	while (token)
	{
		if (token->type == GREAT)
			open_fd2(data, token);
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

t_token	*new_token(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = token;
	tmp2 = token->next;
	token->prev->next = token->next->next;
	if (token->next->next)
	{
		token->next->next->prev = token->prev;
		token = token->next->next;
		free(tmp2);
	}
	else
		token = token->next;
	free(tmp);
	return (token);
}

t_token	*new_token_after_fd(t_token *token)
{
	while (token->next)
	{
		if (token->type == GREAT || token->type == LESS
			|| token->type == HEREDOC)
			token = new_token(token);
		else
			token = token->next;
	}
	while (token->prev->prev)
	{
		if (!token->prev->prev)
			break ;
		token = token->prev;
	}
	return (token);
}
