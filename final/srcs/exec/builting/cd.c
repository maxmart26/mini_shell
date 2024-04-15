/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:12:13 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/12 12:23:22 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"
#include <dirent.h>

char	*ft_env_pwd(t_env *env);

char	*ft_init_pwd_cd(t_env *env)
{
	char	*str;
	char	*buffer;

	str = "PWD=";
	buffer = NULL;
	buffer = getcwd(buffer, _SC_PASS_MAX);
	if (!buffer)
		buffer = ft_env_pwd(env);
	str = ft_strjoin(str, buffer);
	return (str);
}

char	*ft_env_pwd(t_env *env)
{
	while (env)
	{
		if (strncmp(env->name, "PWD", 3) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

char	*ft_init_oldpwd_cd(t_env *env)
{
	char	*str;
	char	*buffer;

	str = "OLDPWD=";
	buffer = NULL;
	buffer = getcwd(buffer, _SC_PASS_MAX);
	if (!buffer)
		buffer = ft_env_pwd(env);
	str = ft_strjoin(str, buffer);
	return (str);
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

void	ft_test(char *buffer_old, t_data *data)
{
	ft_export(token_init("export", buffer_old), data, -1);
}

void	ft_cd_end(char **str, char *buffer, t_data *data, int k)
{
	char	*buffer_old;

	buffer_old = ft_init_oldpwd_cd(data->env);
	if (k == 1)
	{
		if (chdir(str[1]) == -1)
			ft_printf_error("bash: cd: %s: not a directory\n", str[1]);
		else
		{
			buffer = ft_init_pwd_cd(data->env);
			ft_export(token_init("export", buffer), data, -1);
			ft_test(buffer_old, data);
			free(buffer);
		}
	}
}
int	ft_cd(char **str, int i, t_data *data)
{
	char	*buffer;
	int	k;

	k = 1;
	buffer = NULL;
	if (i == 0)
		exit(157);
	if (str[2])
		return (ft_printf_error("bash: cd: too many argument\n"), 1);
	if (str[1] == NULL || (str[1][0] == '~' && strlen(str[1]) == 1))
	{
		buffer = ft_strjoin("/home/", getenv("LOGNAME"));
		chdir(buffer);
		free(buffer);
		buffer = ft_init_pwd_cd(data->env);
		ft_export(token_init("export", buffer), data, -1);
		free(buffer);
		k = 0;
	}
	ft_cd_end(str, buffer, data, k);
	return (0);
}
