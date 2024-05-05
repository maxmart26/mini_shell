/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:12:13 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/05 12:53:44 by matorgue         ###   ########.fr       */
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
		buffer = ft_strdup(ft_env_pwd(env));
	str = ft_strjoin(str, buffer);
	if (buffer != NULL)
		free(buffer);
	return (str);
}

char	*ft_env_pwd(t_env *env)
{
	while (env)
	{
		if (strncmp(env->value, "PWD", 3) == 0)
			return (&env->value[4]);
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
	{
		buffer = ft_env_pwd(env);
		str = ft_strjoin(str, buffer);
	}
	else
	{
		str = ft_strjoin(str, buffer);
		free(buffer);
	}
	return (str);
}

void	ft_cd_end(char **str, char *buffer, t_data *data, t_token *token)
{
	char *(buffer_old) = ft_init_oldpwd_cd(data->env);
	char **(buf) = NULL;
	if (data->k == 1)
	{
		if (chdir(str[1]) == -1)
		{
			data->exit = 1;
			ft_printf_error("bash: cd: %s: No such file or directory\n",
				str[1]);
			free(buffer_old);
		}
		else
		{
			buffer = ft_init_pwd_cd(data->env);
			buf = token_init("export", buffer);
			ft_export(buf, data, -1, token);
			ft_free_tab(buf);
			ft_test(buffer_old, data, token);
			free(buffer);
		}
	}
	else
		free(buffer_old);
}

void	ft_cd_vague(char *buffer, t_data *data, char **buff, t_token *token)
{
	buffer = ft_strjoin("/home/", getenv("LOGNAME"));
	chdir(buffer);
	free(buffer);
	buffer = ft_init_pwd_cd(data->env);
	buff = token_init("export", buffer);
	ft_export(buff, data, -1, token);
	free_tab(buff);
	free(buffer);
	data->k = 0;
	data->exit = 134;
}
