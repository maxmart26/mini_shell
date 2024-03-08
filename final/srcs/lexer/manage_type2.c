/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_type2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:19:10 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/08 14:52:06 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	add_cmd_args(t_token *token)
{
	if (ft_strncmp(token->value, "ls", 2) == 0)
		add_ls_args(token);
	else if (ft_strncmp(token->value, "wc", 2) == 0)
		add_wc_args(token);
	else if (ft_strncmp(token->value, "awk", 3) == 0)
		add_awk_args(token);
	else if (ft_strncmp(token->value, "cat", 3) == 0)
		add_cat_args(token);
	else
		return ;
}

void	add_cmdbuilt_args(t_token *token)
{
	if (ft_strncmp(token->value, "cd", 2) == 0)
		add_cd_args(token);
	if (ft_strncmp(token->value, "echo", 4) == 0)
		add_echo_args(token);
	else if (ft_strncmp(token->value, "export", 6) == 0)
		add_exp_args(token);
	else if (ft_strncmp(token->value, "unset", 5) == 0)
		add_unset_args(token);
	else
		return ;
}

void	add_args(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
	{
		if (tmp->type == CMD)
			add_cmd_args(tmp);
		else if (tmp->type == CMD_BULT)
			add_cmdbuilt_args(tmp);
		tmp = tmp->next;
	}
}
