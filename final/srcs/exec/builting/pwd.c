/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:51:30 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/15 16:35:44 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_end(t_data *data, char **str)
{
	t_token	*token;
	t_token	*tmp;

	token = data->lexer_list;

	while (token)
		token = token->prev;
	ft_free_tab(str);
	free(data->pid);
	if (data->std_int > 2)
		close(data->std_int);
	if (data->std_out > 2)
		close(data->std_out);
	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
	free(data);
}
int	ft_pwd(char **strs, t_data *data)
{
	char	*str;

	ft_dup2(data);
	str = NULL;
	str = getcwd(str, _SC_PASS_MAX);
	if (strs[1] && strncmp(strs[1], "-", 1) == 0)
	{
		printf("%s %s", "bash: pwd: ", strs[1]);
		g_status = 258;
		printf(INV_OPT);
		ft_end(data, strs);
		free(str);
		exit(1);
	}
	else
	{
		printf("%s\n", str);
		free(str);
		ft_end(data, strs);
		exit(0);
	}
}
