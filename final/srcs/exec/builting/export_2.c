/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:22:01 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/26 17:27:22 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_swap(char **env, int i, t_data *data, t_token *token)
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
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				nb++;
			}
				i++;
		}
	}
	i = -1;
	ft_dup2(data, token);
	while (env[i++ + 1])
	{
		printf("declare -x %s\n", env[i]);
	}
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

void	ft_trie_export(t_data *data, t_token *token)
{
	char	**env;
	int		i;
	t_env	*envp;

	envp = data->env;
	i = ft_lstsizee(data->env);
	env = malloc((i + 1) * sizeof(char *));
	if (!env)
		exit(-1);
	i = 0;
	while (envp)
	{
		env[i] = ft_strdup(envp->value);
		envp = envp->next;
		i++;
	}
	env[i] = NULL;
	ft_swap(env, i, data, token);
	free_tab(env);
}

void	ft_export_modif(char *token, t_env *env)
{
	free(env->value);
	env->value = ft_strdup(token);
}

int	verif_export_acsii(unsigned int i, char **str, t_data *data)
{
	if (i == '@' || i == '_' || i == '-' || i == '\\' || i == '%' || i == '+'
		|| (i == '=' && i == '\0') || (i <= '9' && i >= '0'))
	{
		ft_printf_error("bash: export: `%s': not a valid identifier\n", str[1]);
		data->exit = 1;
		// free_tab(str);
		return (1);
	}
	else
		return (0);
}
