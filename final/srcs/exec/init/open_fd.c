/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:28:38 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/28 14:17:07 by matorgue         ###   ########.fr       */
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
			if (data->std_int == -1)
				data->std_int = 0;
			if (data->std_out == -1)
				data->std_out = 1;
			break;
		}
		tmp = token->next;
		token = tmp;
	}
}
t_token	*new_tokenn(t_token *token)
{
	t_token	*new;

	new = NULL;
	if (token->next->next)
	{
		new = token->next->next;
		new->prev = NULL;
	}
	free(token->next->value);
	free(token->next);
	free(token->value);
	free(token);
	if (new)
		new->index = 0;
	return (new);
}
t_token	*new_token(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = token;
	tmp2 = token->next;
	if (token->index == 0)
		return (new_tokenn(token));
	if (token->next->next)
	{
		token->next->next->prev = token->prev;
		if (token->prev)
			token->prev->next = token->next->next;
		token = token->next->next;
	}
	else
	{
		token->prev->next = NULL;
		token = token->prev;
	}
	free(tmp2->value);
	free(tmp2);
	free(tmp->value);
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
	while (token->prev)
	{
		token = token->prev;
	}
	if (strncmp(token->value, "NONE", 4) == 0)
		token = token->next;
	return (token);
}
