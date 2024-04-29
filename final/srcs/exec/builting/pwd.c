/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:51:30 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/28 18:41:37 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_free_enve(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	ft_end2(t_data *data, t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
	ft_free_enve(data->env);
	free(data);
}

void	ft_end(t_data *data, char **str)
{
	t_token	*token;

	token = data->lexer_list;
	ft_free_tab(str);
	free(data->pid);
	while (data->nb_pipe >= 1)
	{
		free(data->pipe_fd[data->nb_pipe - 1]);
		if (data->nb_pipe == 1)
			break ;
		data->nb_pipe--;
	}
	if (data->nb_pipe > 0)
		free(data->pipe_fd);
	if (data->std_int > 2)
		close(data->std_int);
	if (data->std_out > 2)
		close(data->std_out);
	ft_end2(data, token);
}

int	ft_pwd(char **strs, t_data *data, t_token *token)
{
	char	*str;

	ft_dup2(data, token);
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
