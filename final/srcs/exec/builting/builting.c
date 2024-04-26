/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:19:11 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/26 13:18:12 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	fd_built(t_data *data, t_token *token)
{
	char	**str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(token->value);
	if (token->value[len - 1] == ' ')
	{
		str = ft_split(token->value, ' ');
		while (str[i])
			i++;
		i--;
		str[i] = ft_strjoin(str[i], " ");
	}
	else
		str = ft_split(token->value, ' ');
	which_built(data, str);
}

void	redirection_builting(t_token *token, t_data *data)
{
	if (token->type == CMD)
		ft_exec(data, token);
	if (token->type == CMD_ABS)
		ft_exec_abs(token, data);
}

void	ft_test(char *buffer_old, t_data *data, t_token *token)
{
	char	**str;

	str = token_init("export", buffer_old);
	ft_export(str, data, -1, token);
	free(buffer_old);
	ft_free_tab(str);
}

void	cd_end(t_data *data, char **str)
{
	ft_end(data, str);
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
