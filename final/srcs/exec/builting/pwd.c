/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:51:30 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/27 14:17:22 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

int	ft_pwd(t_token *token)
{
	char	*str;
	t_token	*tmp;

	tmp = token;
	str = NULL;
	str = getcwd(str, _SC_PASS_MAX);
	if (strncmp(&tmp->next->value[0], "-", 1) == 0)
	{
		printf("%s %s", "bash: pwd: ", tmp->next->value);
		g_status = 258;
		return (printf(INV_OPT), 1);
	}
	else
	{
		printf("%s\n", str);
		return (0);
	}
}
