/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:27:53 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/25 18:28:50 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_include.h"
#include "../include/minishell_proto.h"
#include "../include/minishell_struct.h"

void	init_values(t_data *tools)
{
	tools->lexer_list = NULL;
	tools->pid = NULL;
	tools->nb_pipe = 0;
	tools->std_int = 1;
	tools->lexer_list = NULL;
	tools->pid = 0;
	tools->std_out = 0;
	tools->status = 1;
	tools->exit = 0;
	tools->exit_status = 0;
	tools->exit = 0;
	tools->in_cmd = 0;
	tools->in_heredoc = 0;
	tools->first_call = 1;
}
