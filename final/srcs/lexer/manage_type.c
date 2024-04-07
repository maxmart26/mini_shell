/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:38:37 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/07 14:08:14 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	manage_cmd_buil(t_token *token)
{
	if (ft_strlen(token->value) == 2
		&& ft_strncmp(token->value, "cd", 2) == 0)
		token->type = CMD_BULT;
	else if (ft_strlen(token->value) == 4
		&& ft_strncmp(token->value, "echo", 4) == 0)
		token->type = CMD_BULT;
	else if (ft_strlen(token->value) == 3
		&& ft_strncmp(token->value, "pwd", 3) == 0)
		token->type = CMD_BULT;
	else if (ft_strlen(token->value) == 6
		&& ft_strncmp(token->value, "export", 6) == 0)
		token->type = CMD_BULT;
	else if (ft_strlen(token->value) == 5
		&& ft_strncmp(token->value, "unset", 5) == 0)
		token->type = CMD_BULT;
	else if (ft_strlen(token->value) == 3
		&& ft_strncmp(token->value, "env", 3) == 0)
		token->type = CMD_BULT;
	else if (ft_strlen(token->value) == 4
		&& ft_strncmp(token->value, "exit", 4) == 0)
		token->type = CMD_BULT;
}

void	manage_cmd(t_token *token)
{
	if (ft_strlen(token->value) == 2
		&& ft_strncmp(token->value, "ls", 2) == 0)
		token->type = CMD;
	else if (ft_strlen(token->value) == 2
		&& ft_strncmp(token->value, "wc", 2) == 0)
		token->type = CMD;
	else if (ft_strlen(token->value) == 3
		&& ft_strncmp(token->value, "awk", 3) == 0)
		token->type = CMD;
	else if (ft_strlen(token->value) == 3
		&& ft_strncmp(token->value, "cat", 3) == 0)
		token->type = CMD;
	else if (ft_strlen(token->value) == 4
		&& ft_strncmp(token->value, "grep", 4) == 0)
		token->type = CMD;
	else if (ft_strlen(token->value) == 5
		&& ft_strncmp(token->value, "clear", 5) == 0)
		token->type = CMD;
	else if (ft_strlen(token->value) == 3
		&& ft_strncmp(token->value, "tac", 3) == 0)
		token->type = CMD;
}

void	add_cmd(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->value, "cd", 2) == 0
			|| ft_strncmp(tmp->value, "echo", 4) == 0
			|| ft_strncmp(tmp->value, "pwd", 3) == 0
			|| ft_strncmp(tmp->value, "export", 6) == 0
			|| ft_strncmp(tmp->value, "unset", 5) == 0
			|| ft_strncmp(tmp->value, "env", 3) == 0
			|| ft_strncmp(tmp->value, "exit", 4) == 0)
			manage_cmd_buil(tmp);
		else
			manage_cmd(tmp);
		tmp = tmp->next;
	}
}
