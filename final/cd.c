/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:12:13 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/11 12:39:45 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"
#include <dirent.h>

char	*ft_init_pwd_cd(void)
{
	char	*str;
	char	*buffer;

	str = "PWD=";
	buffer = getcwd(buffer, _SC_PASS_MAX);
	str = ft_strjoin(str, buffer);
	return (str);
}
char	*ft_init_oldpwd_cd(void)
{
	char	*str;
	char	*buffer;

	str = "OLDPWD=";
	buffer = getcwd(buffer, _SC_PASS_MAX);
	str = ft_strjoin(str, buffer);
	// printf("%s\n", str);
	return (str);
}
int	ft_count(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("%s\n", str);
	while (str[i])
	{
		//printf("%c\n", str[i]);
		if (str[i] == '/')
			j = i;
		i++;
	}
	return (j);
}

static char	*ft_cutt(char *str, int i)
{
	char	*buffer;
	int		j;

	j = 0;
	printf("ici1\t%s\n",str);
	//printf("ici2\t%s\n",buffer);
	buffer = malloc(i + 1 * sizeof(char));
	if (!buffer)
		exit(EXIT_FAILURE);
	while (j < i)
	{
		buffer[j] = str[j];
		j++;
	}
	buffer[++j] = '\0';
	printf("ici2\t%s\n",buffer);
	return (buffer);
}
char	*ft_cd_cut(void)
{
	char	*str;
	char	*buffer;
	int		i;

	buffer = getcwd(buffer, _SC_PASS_MAX);
	printf("ici\t%s\n",buffer);
	i = ft_count(buffer);
	str = buffer;
	buffer = ft_cutt(str, i);
	printf("ici\t%s\n",buffer);
	return (buffer);
}
void	ft_test(char *buffer_old, t_data *data)
{
	ft_export(token_init("export", buffer_old), data, -1);
}
void	ft_cd(t_token *token, int i, t_data *data)
{
	char	*str;
	char	*buffer;
	char	*buffer_old;

	if (i == 0)
		exit(157);
	str = token->next->value;
	ft_pwd();
	printf("\t\t%s\n", str);
	if (!str)
	{
		str = "/home/";
		str = ft_strjoin(str, getenv("LOGNAME"));
		chdir(str);
		ft_pwd();
		exit(EXIT_SUCCESS);
	}
	// free(buffer);
	buffer_old = ft_init_oldpwd_cd();
	if (ft_strncmp(str, "..", 2) == 0 && ft_strlen(str) == 2)
		str = ft_cd_cut();
	if (chdir(str) == -1)
	{
		printf("test\n");
		// perror("");
		// exit(EXIT_FAILURE);
	}
	else
	{
		chdir(str);
		buffer = ft_init_pwd_cd();
		//printf("%s\n", buffer);
		ft_export(token_init("export", buffer), data, -1);
		// free(buffer);
		ft_pwd();
		// exit(EXIT_SUCCESS);
		ft_test(buffer_old, data);
	}
}
