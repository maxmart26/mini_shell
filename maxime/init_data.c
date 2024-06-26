/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:04 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/06 15:25:46 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"

void	nb_pipe(t_token *token, t_data *data)
{
	t_token	*tmp;
	int i;

	i = 0;
	data->nb_pipe = 0;
	while (token)
	{
		if (token->type == PIPE)
			data->nb_pipe++;
		tmp = token->next;
		token = tmp;
	}
	data->pipe_fd = malloc(data->nb_pipe * sizeof(int *));
	if (!data->pipe_fd)
		exit(0);
	while(i < data->nb_pipe)
	{
		data->pipe_fd[i] = malloc(2 * sizeof(int));
		if (pipe(data->pipe_fd[i]) == -1)
		{
			close(data->std_int);
			close(data->std_out);
			i--;
			while(i >= 0)
			{
				close(data->pipe_fd[i][0]);
				close(data->pipe_fd[i][1]);
				i--;
			}
			exit(0);
		}
		printf("%d avec %d\n", data->pipe_fd[i][0], data->pipe_fd[i][1]);
		i++;
	}
}
void	init_data(t_token *token, t_data *data, char **envp)
{
	data->nb_pipe = 0;
	data->nb_cmd = 0;
	data->envp = envp;
	data->std_out = 1;
	data->std_int = 0;
	nb_pipe(token,data);
}

t_env	*new_env()
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}
t_env	*init_env_i()
{
	t_env	*env;
	char	*str;

	//printf("test\n");
	env = new_env();
	env->prev = NULL;
	env->next = NULL;
	str = NULL;
	str = getcwd(str, _SC_PASS_MAX);
	str = ft_strjoin("PWD=", str);
	env->next = new_env();
	env->next->value = "SHLVL=1";
	env->next->prev = env;
	env->value = str;
	env->next->next = new_env();
	env->next->next->value = "_=/usr/bin/env";
	env->next->next->prev = env->next;
	return (env);
}

t_env	*init_env(t_data *data)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*result;
	char	**str;
	int	i;

	if (!data->envp[0])
		return (init_env_i());
	env = new_env();
	i = 0;
	result = env;
	env->prev = NULL;
	while (data->envp[i])
	{
		env->value = data->envp[i];
		str = ft_split(env->value, '=');
		env->name = str[0];
		env->content = str[1];
		free(str);
		if (data->envp[i + 1])
		{
			env->next = new_env();
			tmp = env->next;
			tmp->prev = env;
			env = tmp;
		}
		i++;
	}
	return (result);
}


