/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_abs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:56:01 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/25 15:24:22 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_exec_abs(t_token *token, t_data *data)
{
	char	*path_def;
	char	*tmp;
	char	**mycmdargs;

	if (token->next && token->next->type == ARG)
	{
		path_def = ft_strjoin(token->value, " ");
		tmp = ft_strjoin(path_def, token->next->value);
		mycmdargs = ft_split(tmp, ' ');
		free(path_def);
		free(tmp);
	}
	else
	{
		mycmdargs = ft_split(token->value, ' ');
	}
	ft_dup2(data);
	if (access(token->value, 0) == 0)
		execve(token->value, mycmdargs, data->envp);
}
