/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:38:09 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/20 11:09:05 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	new_line_init(t_data *tools)
{
	tools->nl_error = 0;
	tools->first_call = 0;
	if (tools->exit_status == 258)
		tools->exit_status = 0;
}

int	new_line_error(t_data *tools)
{
	int	i;

	i = -1;
	if (tools->args == NULL)
		return (tools->nl_error = 1, 1);
	if (tools->args[0] == '\0')
		return (tools->nl_error = 1, 1);
	if (!count_quotes(tools->args))
		return (tools->nl_error = 2, 1);
	while (tools->args[++i])
	{
		if (is_char(tools->args[i], '\0'))
			return (0);
		if (is_space(tools->args[i]))
		{
			while (is_space(tools->args[i]) && tools->args[i])
				i++;
			if (tools->args[i] == '\0')
				return (tools->nl_error = 1, 1);
		}
	}
	return (0);
}

void	check_new_line(t_data *tools)
{
	new_line_init(tools);
	if (new_line_error(tools))
		return ;
}
