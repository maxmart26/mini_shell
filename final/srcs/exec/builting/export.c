/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/07 14:04:02 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_swap(char **env, int i)
{
	int		nb;
	char	*tmp;

	nb = 1;
	while (nb > 0)
	{
		nb = 0;
		i = 0;
		while (env[i + 1])
		{
			if (strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				nb++;
			}
			else
				i++;
		}
	}
	i = -1;
	while (env[i++ + 1])
		printf("declare -x %s\n", env[i]);
}

int	ft_lstsizee(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void	ft_trie_export(t_data *data)
{
	char	**env;
	int		i;
	t_env	*envp;

	envp = data->env;
	i = ft_lstsizee(data->env);
	env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp)
	{
		env[i] = envp->value;
		envp = envp->next;
		i++;
	}
	ft_swap(env, i);
}

void	ft_export_modif(char *token, t_env *env, char **str)
{
	env->value = token;
	free(env->name);
	free(env->content);
	env->content = str[1];
	env->name = str[0];
	free_tab(str);
}

int	ft_expor_ex(char *tmp, t_data *data, char **str)
{
	t_env	*init;

	init = data->env;
	while (init)
	{
		printf("le env = %s avec le str = %s\n\n", init->name, str[0]);
		if (ft_strncmp(init->name, str[0], ft_strlen(str[0])) == 0
			&& ft_strlen(str[0]) == ft_strlen(init->name))
		{
			ft_export_modif(tmp, init, str);
			return (0);
		}
		init = init->next;
	}
	return (1);
}

void	ft_export(char **strs, t_data *data, int i)
{
	char	**str;

	if (i == 0)
		exit(156);
	if (strs[1] == NULL)
		ft_trie_export(data);
	else
	{
		str = ft_split(strs[1], '=');
		printf("test1\n");
		if (ft_expor_ex(strs[1], data, str) == 1)
		{
			if (!data->env)
			{
				data->env = new_env();
				data->env->value = strs[1];
				data->env->content = str[1];
				data->env->name = str[0];
				free_tab(str);
			}
			else
			{
				printf("test2\n");
				while (data->env->next)
					data->env = data->env->next;
				data->env->next = new_env();
				data->env->next->value = strs[1];
				data->env->next->prev = data->env;
				data->env->next->content = str[1];
				data->env->next->name = str[0];
				free_tab(str);
				while (data->env->prev)
					data->env = data->env->prev;
			}
		}
	}
}
