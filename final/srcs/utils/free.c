/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:51:08 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/02 18:28:58 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	free_minishell(t_data *tools)
{
	free(tools->args);
	free_env(tools->envp);
	ft_destroy_env(tools->env);
	destroy_token_list(tools->lexer_list);
	free(tools->pid);
	free(tools);
}

void	free_minishell_ctrld(t_data *tools)
{
	// t_token	*token;

	// token = tools->lexer_list;
	if (tools->envp)
		ft_destroy_env(tools->env);
	free(tools->args);
	free(tools);
}
