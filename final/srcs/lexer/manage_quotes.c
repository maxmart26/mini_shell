/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:23:02 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/05 19:25:18 by lnunez-t         ###   ########.fr       */
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
	word = ft_substr(line, *j, i - *j);
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

int	quote_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	which_quote(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			quote = 1;
			break ;
		}
		else if (str[i] == '\'')
		{
			quote = 2;
			break ;
		}
		i++;
	}
	return (quote);
}

char	*delete_sep(char *str)
{
	char	*result;
	int		i
	int		j;
	int		espacePrecedent;

	i = 0;
	result = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	espacePrecedent = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			result[j++] = str[i++];
			espacePrecedent = 0;
		}
		else if (!espacePrecedent)
		{
			str[j++] = ' ';
			espacePrecedent = 1;
			i++;
		}
		else
		{
			i++;
		}
	}
	result[j] = '\0';
	return (result);
}

char	*delete_quotes(char *str)
{
	char	*result;
	char	**cut;
	int		i;

	result = NULL;
	i = 0;
	cut = malloc(sizeof(char) * (ft_strlen(str) - 2));
	if (!cut)
		return (NULL);
	if (which_quote(str) == 1)
		cut = ft_split(str, '\"');
	else if (which_quote(str) == 2)
		cut = ft_split(str, '\'');
	while (cut[i])
	{
		result = ft_strjoin(result, cut[i]);
		i++;
	}
	return (result);
}

void	remove_quotes(t_token *lexer_list)
{
	t_token	*tmp;

	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			while (quote_in_str(tmp->value) == 1)
			{
				tmp->value = delete_quotes(tmp->value);
			}
			printf("%s\n", tmp->value);
			tmp->value = delete_sep(tmp->value);
		}
		tmp = tmp->next;
	}
}
