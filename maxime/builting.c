/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:19:11 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/05 18:53:21 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"

void	redirection_builting(t_token *token, t_data *data)
{
	if (token->type == CMD)
		ft_exec(data, token);
	if (ft_strncmp(token->value, "echo", 5) == 0
		&& ft_strlen(token->value) == 5)
		ft_echo(token);
	if (ft_strncmp(token->value, "pwd", 3) == 0 && ft_strlen(token->value) == 3)
		ft_pwd();
	if (ft_strncmp(token->value, "env", 3) == 0 && ft_strlen(token->value) == 3)
		ft_env(data);
	if (ft_strncmp(token->value, "cd", 3) == 0 && ft_strlen(token->value) == 3)
		ft_cd(token);
	if (ft_strncmp(token->value, "export", 6) == 0
		&& ft_strlen(token->value) == 6)
		ft_export(token, data, data->nb_pipe);
	if (ft_strncmp(token->value, "unset", 5) == 0
		&& ft_strlen(token->value) == 5)
		ft_unset(token, data, data->nb_pipe);
}
