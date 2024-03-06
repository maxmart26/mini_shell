/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:12:13 by matorgue          #+#    #+#             */
/*   Updated: 2024/02/28 17:15:36 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"
#include <dirent.h>

void	ft_cd(t_token *token)
{
	char	*str;

	str = token->next->value;
	ft_pwd();
	if (!str)
	{
		str = "/home/";
		str = ft_strjoin(str, getenv("LOGNAME"));
		chdir(str);
		ft_pwd();
		exit (EXIT_SUCCESS);
	}
	if (chdir(str) == -1)
	{
		perror("");
		ft_pwd();
		exit (EXIT_FAILURE);
	}
	else
	{
		chdir(str);
		ft_pwd();
		exit (EXIT_SUCCESS);
	}
}
