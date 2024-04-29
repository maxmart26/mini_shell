/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:00:41 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/29 15:47:34 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

static int	check_quote(int c)
{
	if (c == 92)
		return (1);
	else if (c == 39)
		return (2);
	else if (c == 34)
		return (3);
	else
		return (0);
}

char	*get_str(char *str, int *j, char *word, int *nb_quote)
{
	char	*tmp;
	char	*line;

	if (*nb_quote == 0)
	{
		tmp = word;
		line = get_nq_word(str, j);
		word = ft_strjoin(word, line);
		free(tmp);
		free(line);
	}
	else if (*nb_quote > 0)
	{
		tmp = word;
		line = get_q_word(str, j, *nb_quote);
		word = ft_strjoin(word, line);
		free(tmp);
		free(line);
		*nb_quote = -1;
	}
	return (word);
}

void	get_word(t_token *token_list, char *str, int *i, int *index)
{
	int		nb_quote;
	char	*word;
	int		j;

	j = *i;
	word = NULL;
	nb_quote = 0;
	while (str[j])
	{
		nb_quote = check_quote(str[j]);
		word = get_str(str, &j, word, &nb_quote);
		if (str[j - 1] == '\0')
			break ;
		if (ft_strrchr("\t ><|", str[j]))
			break ;
	}
	add_token(token_list, WORD, word, *index);
	*i = *i + ft_strlen(word);
	(*index)++;
	free(word);
}
