/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:12:13 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/07 14:09:14 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"
#include <dirent.h>

char	*ft_init_pwd_cd(void)
{
	char	*str;
	char	*buffer;

	str = "PWD=";
	buffer = NULL;
	buffer = getcwd(buffer, _SC_PASS_MAX);
	str = ft_strjoin(str, buffer);
	return (str);
}

char	*ft_init_oldpwd_cd(void)
{
	char	*str;
	char	*buffer;

	str = "OLDPWD=";
	buffer = NULL;
	buffer = getcwd(buffer, _SC_PASS_MAX);
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

void	ft_cd(char **str, int i, t_data *data)
{
	char	*buffer;
	char	*buffer_old;

	if (i == 0)
		exit(157);
	if (str[1] == NULL)
	{
		buffer = ft_strjoin("/home/", getenv("LOGNAME"));
		chdir(buffer);
		free(buffer);
	}
	else if (str[2])
	{
		printf("bash: cd: too many argument\n");
		return ;
	}
	buffer_old = ft_init_oldpwd_cd();
	if (chdir(str[1]) == -1)
		perror("error\n");
	else
	{
		buffer = ft_init_pwd_cd();
		ft_export(token_init("export", buffer), data, -1);
		ft_test(buffer_old, data);
	}
}
