/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:51:08 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/15 17:02:41 by lnunez-t         ###   ########.fr       */
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
	/*t_env	*current;
	t_env	*next;

	current = tools->env;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current->content);
		free(current);
		current = next;
	}*/
	free(tools->args);
	free(tools);
}
