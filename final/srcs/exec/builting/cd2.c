/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:10:45 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/29 16:11:28 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_cd_pasta(char *buffer, t_data *data, char **buff, t_token *token)
{
	buffer = getenv("OLDPWD");
	chdir(buffer);
	buffer = ft_init_pwd_cd(data->env);
	buff = token_init("export", buffer);
	ft_export(buff, data, -1, token);
	free_tab(buff);
	free(buffer);
	data->k = 0;
	data->exit = 134;
}

int	ft_cd(char **str, int i, t_data *data, t_token *token)
{
	char **(buff) = NULL;
	char *(buffer) = NULL;
	data->k = 1;
	if (i == 0)
		cd_end(data, str);
	if (str[1] && str[2])
	{
		data->exit = 1;
		return (ft_printf_error("bash: cd: too many arguments\n"), 1);
	}
	if (str[1] == NULL || (str[1][0] == '~' && strlen(str[1]) == 1))
		ft_cd_vague(buffer, data, buff, token);
	else if ((str[1][0] == '-' && strlen(str[1]) == 1))
		ft_cd_pasta(buffer, data, buff, token);
	ft_cd_end(str, buffer, data, token);
	return (0);
}
