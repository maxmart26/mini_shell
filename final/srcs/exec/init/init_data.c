/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:04 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/19 15:43:20 by matorgue         ###   ########.fr       */
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
		//new->name = NULL;
		new->value = NULL;
		//new->content = NULL;
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
	//env->content = str;
	//env->name = ft_strdup("PWD");
	env->next = new_env();
	env->next->value = ft_strdup("SHLVL=1");
	//env->next->name = ft_strdup("SHLVL");
	//env->next->content = ft_strdup("1");
	env->next->prev = env;
	env->value = str;
	env->next->next = new_env();
	//env->next->next->name = ft_strdup("_");
	//env->next->next->content = ft_strdup("/usr/bin/env");
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

	env = NULL;
	env = new_env();
	str = NULL;
	if (!env)
		return (NULL);
	result = env;
	env->prev = NULL;
	while (data->envp[i])
	{
		env->value = ft_strdup(data->envp[i]);
		str = ft_split(env->value, '=');
		if (!str)
		{
			ft_destroy_env(result);
			return (NULL);
		}
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
