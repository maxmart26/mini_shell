/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:04 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/13 17:57:19 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	nb_pipe(t_token *token, t_data *data)
{
	t_token	*tmp;
	int		i;

	i = 0;
	data->nb_pipe = 0;
	while (token)
	{
		if (token->type == PIPE)
			data->nb_pipe++;
		tmp = token->next;
		token = tmp;
	}
	if (data->nb_pipe > 0)
	{
		data->pipe_fd = malloc(data->nb_pipe * sizeof(int *));
		if (!data->pipe_fd)
			exit(0);
	}
	while (data->nb_pipe > i)
	{
		data->pipe_fd[i] = malloc(2 * sizeof(int));
		if (pipe(data->pipe_fd[i]) == -1)
			exit(0);
		printf("%d avec %d\n", data->pipe_fd[i][0], data->pipe_fd[i][1]);
		i++;
	}
}

void	init_data(t_token *token, t_data *data)
{
	data->nb_pipe = 0;
	data->nb_cmd = 0;
	nb_pipe(token, data);
}

t_env	*new_env(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new)
	{
		new->next = NULL;
		new->name = NULL;
		new->value = NULL;
		new->content = NULL;
	}
	return (new);
}

t_env	*init_env_i(void)
{
	t_env	*env;
	char	*str;

	env = new_env();
	env->prev = NULL;
	env->next = NULL;
	str = NULL;
	str = getcwd(str, _SC_PASS_MAX);
	str = ft_strjoin("PWD=", str);
	env->next = new_env();
	env->next->value = ft_strdup("SHLVL=1");
	env->next->prev = env;
	env->value = str;
	env->next->next = new_env();
	env->next->next->value = ft_strdup("_=/usr/bin/env");
	env->next->next->prev = env->next;
	init_end(env);
	free(str);
	return (env);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	free_env_str(char **str)
{
	int	i;

	i = 2;
	if (!str[2])
		return ;

	if (str[i][0])
	{
	while (str[i])
	{
		if (str[i] == NULL)
			break;
		free(str[i]);
		i++;
	}
	}
	free(str);
}

t_env	*init_env(t_data *data, int i)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*result;
	char	**str;

	env = new_env();
	if (!env)
		return (NULL);
	result = env;
	env->prev = NULL;
	while (data->envp[i])
	{
		env->value = data->envp[i];
		str = ft_split(env->value, '=');
		if (!str)
		{
			ft_destroy_env(result);
			return (NULL);
		}
		env->name = ft_strdup(str[0]);
		env->content = ft_strdup(str[1]);
		ft_free_tab(str);
		if (data->envp[i + 1])
		{
			env->next = new_env();
			if (!env->next)
			{
				ft_destroy_env(result);
				return (NULL);
			}
			tmp = env->next;
			tmp->prev = env;
			env = tmp;
		}
		i++;
	}
	return (result);
}
