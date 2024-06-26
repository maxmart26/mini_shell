/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/05 14:27:13 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_export_modif(t_token *token, t_env *env, char **str)
{
	env->value = token->next->value;
	printf("%s\n", str[1]);
	free(env->name);
	free(env->content);
	env->content = str[1];
	env->name = str[0];
	free(str);
}

int	ft_export_ex(t_token *token, t_data *data, char **str)
{
	t_env	*init;

	init = data->env;
	// printf("%s\n",init->value);
	while (init->next)
	{
		if (ft_strncmp(init->name, str[0], ft_strlen(str[0])) == 0
			&& ft_strlen(str[0]) == ft_strlen(init->name))
		{
			// printf("\n\n\n\n\t\ttest\n");
			ft_export_modif(token, init, str);
			return (0);
		}
		init = init->next;
	}
	while (init->prev)
		init = init->prev;
	return (1);
}

char	*ft_modif(char **str)
{
	long	nb;
	long	result;

	result = 0;
	printf("%s\n", str[1]);
	nb = ft_atol(str[1]);
	printf("%ld\n", nb);
	if (nb < 0)
		nb = 0;
	else if (nb > 1000)
		nb = 1;
	return (ft_itoa(nb));
}

void	ft_swap(char **env, int i)
{
	char	*tmp;
	char	nb;

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
	while (envp->next)
	{
		env[i] = envp->value;
		envp = envp->next;
		i++;
	}
	ft_swap(env, i);
}
void	ft_export(t_token *token, t_data *data, int i)
{
	char	**str;
	char	*tmp;

	if (i == 0)
		exit(156);
	if (token->next->type != 5)
		ft_trie_export(data);
	else
	{
		str = ft_split(token->next->value, '=');
		if (ft_strncmp(str[0], "SHLVL", 5) == 0 && ft_strlen(str[0]) == 5)
		{
			str[1] = ft_modif(str);
			token->next->value = ft_strjoin(str[0], "=");
			tmp = token->next->value;
			token->next->value = ft_strjoin(tmp, str[1]);
			free(tmp);
			tmp = token->next->value;
		}
		printf("%s\n", str[1]);
		if (ft_export_ex(token, data, str) == 1)
		{
			if (!data->env)
			{
				data->env = new_env();
				data->env->value = token->next->value;
				data->env->content = str[1];
				data->env->name = str[0];
				free(str);
			}
			else
			{
				while (data->env->next)
					data->env = data->env->next;
				data->env->next = new_env();
				data->env->next->value = token->next->value;
				data->env->next->prev = data->env;
				data->env->next->content = str[1];
				data->env->next->name = str[0];
				free(str);
				while (data->env->prev)
					data->env = data->env->prev;
			}
		}
		if (tmp != NULL)
			if (i > 0)
				exit(0);
	}
}
