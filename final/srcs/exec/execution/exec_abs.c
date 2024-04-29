/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_abs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:56:01 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/28 18:03:28 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_exec_abs(t_token *token, t_data *data)
{
	char	**str;

	str = ft_split(token->value, ' ');
	if (access(str[0], 0) == 0)
	{
		ft_dup2(data, token);
		execve(str[0], str, data->envp);
	}
	free_tab(str);
}

void	ft_free_tab(char **input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		input[i] = NULL;
		i++;
	}
	free(input);
	input = NULL;
}
