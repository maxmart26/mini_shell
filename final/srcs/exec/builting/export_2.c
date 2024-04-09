/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:22:01 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/08 16:22:31 by matorgue         ###   ########.fr       */
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