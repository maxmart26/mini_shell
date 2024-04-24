/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:24:20 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/24 14:39:19 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	count_words(char c, char *s)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i] && s[i + 1])
	{
		if (s[i] != c && (((s[i + 1] == '\0') || s[i + 1] == c)))
			words++;
		i++;
	}
	return (words);
}

static void	fill_tab(char *dest, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
}

void	free_tab(char **dest)
{
	size_t	i;

	i = 0;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
	return ;
}

static void	set_mem(char **dest, char const *s, char c)
{
	size_t	count;
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (s[index])
	{
		count = 0;
		while (s[index + count] && s[index + count] != c)
			count++;
		if (count > 0)
		{
			dest[i] = malloc(sizeof(char) * (count + 1));
			if (!dest[i])
				return (free_tab(dest));
			fill_tab(dest[i], (s + index), c);
			i++;
			index += count;
		}
		else
			index++;
	}
	dest[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	words;

	words = count_words(c, (char *)s);
	dest = (char **)malloc((words + 2) * sizeof(char *));
	if (!dest)
		return (free(dest), NULL);
	set_mem(dest, s, c);
	return (dest);
}
