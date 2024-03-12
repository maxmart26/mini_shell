/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:06:12 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/12 15:01:36 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	ft_here_doc_put_in(t_data *data, char *av)
{
	char	*ret;

	while (1)
	{
		ft_putstr_fd(">", 2);
		ret = get_next_line(0);
		if (ft_strncmp(ret, av, ft_strlen(av)) == 0
			&& ft_strlen(av) == ft_strlen(ret) - 1)
		{
			free(ret);
			return ;
		}
		ft_putstr_fd(ret, data->f1);
		free(ret);
	}
}

int	ft_access(void)
{
	int	i;

	i = 0;
	while (1)
	{
		if (access(ft_strjoin("/tmp/.here_doc", ft_itoa(i)), F_OK) == -1)
			break ;
		else
			i++;
	}
	return (i);
}

void	ft_herdoc(t_data *data, t_token *tmp, int i)
{
	i = ft_access();
	data->itoa = ft_strjoin("/tmp/.here_doc", ft_itoa(i));
	data->f1 = open((data->itoa),
			O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data->f1 < 0)
		return ;
	ft_here_doc_put_in(data, tmp->next->value);
	close(data->f1);
	data->f1 = open(data->itoa, O_RDONLY);
	unlink(data->itoa);
	free(data->itoa);
	data->fd_in = data->f1;
}
void	open_heredoc(t_data *data)
{
	t_token	*tmp;

	tmp = data->lexer_list;
	while (tmp->next)
	{
		if (tmp->type == HEREDOC)
			ft_herdoc(data, tmp, 0);
		tmp = tmp->next;
	}
}
