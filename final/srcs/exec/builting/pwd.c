/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:51:30 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/05 22:12:10 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

int	ft_pwd(char **strs)
{
	char	*str;

	str = NULL;
	str = getcwd(str, _SC_PASS_MAX);
	if (strs[1] && strncmp(strs[1], "-", 1) == 0)
	{
		printf("%s %s", "bash: pwd: ", strs[1]);
		g_status = 258;
		printf(INV_OPT);
		exit (1);

	}
	else
	{
		printf("%s\n", str);
		exit (0);
	}
}
