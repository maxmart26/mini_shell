/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:51:08 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/15 13:25:46 by matorgue         ###   ########.fr       */
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
	free(tools);
}

void	free_minishell_ctrld(t_data *tools)
{
	if (tools->envp)
		ft_destroy_env(tools->env);
	free(tools->args);
	free(tools);
}
