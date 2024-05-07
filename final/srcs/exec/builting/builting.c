/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:19:11 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/07 15:36:08 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	fd_built(t_data *data, t_token *token)
{
	char	**str;

	str = token->str;
	if (ft_strncmp(str[0], "echo", 4) == 0 && ft_strlen(str[0]) == 4)
		ft_echo(str, data, token);
	if (ft_strncmp(str[0], "pwd", 3) == 0 && ft_strlen(str[0]) == 3)
		ft_pwd(str, data, token);
	if (ft_strncmp(str[0], "env", 3) == 0 && ft_strlen(str[0]) == 3)
		ft_env(data, token);
	if (ft_strncmp(str[0], "cd", 2) == 0 && ft_strlen(str[0]) == 2)
		ft_cd(str, data->nb_pipe, data, token);
	if (ft_strncmp(str[0], "export", 6) == 0 && ft_strlen(str[0]) == 6)
		ft_export(str, data, data->nb_pipe, token);
	if (ft_strncmp(str[0], "exit", 4) == 0 && ft_strlen(str[0]) == 4)
		ft_exit(data, data->nb_pipe, str);
	if (ft_strncmp(str[0], "unset", 5) == 0 && ft_strlen(str[0]) == 5)
		ft_unset(str, data, data->nb_pipe);
}

void	ft_test(char *buffer_old, t_data *data, t_token *token)
{
	char	**str;

	str = token_init("export", buffer_old);
	ft_export(str, data, -1, token);
	free(buffer_old);
	ft_free_tab(str);
}

void	cd_end(t_data *data)
{
	ft_end(data);
	exit(157);
}

int	ft_count(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	return (j);
}
