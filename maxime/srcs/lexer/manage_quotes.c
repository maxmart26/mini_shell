/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:23:02 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/22 16:15:32 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*get_nq_word(char *line, int *j)
{
	char	*word;
	int		i;

	i = *j;
	while (line[i] && !ft_strrchr("\t '\"\\<>;|", line[i]))
		i++;
	word = ft_substr(line, *j, i - *j);
	*j = i;
	return (word);
}

char	*get_dq_word(char *line, int *j, int i)
{
	char	*word;

	word = NULL;
	while (line[i] && line[i] != '"')
		i++;
	word = ft_substr(line, *j, i - *j + 1);
	*j = i + 1;
	return (word);
}

char	*get_q_word(char *line, int *j, int nb_quote)
{
	int		i;
	char	*word;

	i = *j;
	word = NULL;
	if (nb_quote == 1)
	{
		word = ft_substr(line, *j, 2);
		*j += 2;
		return (word);
	}
	if (nb_quote == 2)
	{
		i++;
		while (line[i] && line[i] != '\'')
			i++;
		word = ft_substr(line, *j, i - *j + 1);
		*j = i + 1;
		return (word);
	}
	else if (nb_quote == 3)
		return (get_dq_word(line, j, ++i));
	return (word);
}
