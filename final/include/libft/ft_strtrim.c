/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:30:27 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/05 16:30:47 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_begin(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		is_in_set;

	i = 0;
	j = 0;
	is_in_set = 0;
	while (s1[i])
	{
		is_in_set = 0;
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				is_in_set = 1;
			j++;
		}
		if (!is_in_set)
			break ;
		i++;
	}
	return ((char *)s1 + i);
}

static char	*find_end(char const *s1, char const *set, char const *begin)
{
	size_t	i;
	size_t	j;
	int		is_in_set;

	i = ft_strlen(s1) - 1;
	j = 0;
	is_in_set = 0;
	while (s1 + i >= begin)
	{
		is_in_set = 0;
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				is_in_set = 1;
			j++;
		}
		if (!is_in_set)
			break ;
		i--;
	}
	if (s1 + i < begin)
		return ((char *)begin);
	return ((char *)s1 + i);
}

static char	*new_str(char const *begin, char const *end)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char *)malloc(sizeof(char) * (end - begin + 2));
	if (!new)
		return (free(new), NULL);
	while (begin + i <= end)
	{
		new[i] = begin[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*begin;
	char	*end;
	char	*new;

	begin = find_begin(s1, set);
	end = find_end(s1, set, s1);
	if (!s1[0] || end < begin)
	{
		new = (char *)malloc(sizeof(char) * 1);
		if (!new)
			return (free(new), NULL);
		new[0] = '\0';
	}
	else
		new = new_str(begin, end);
	if (!new)
		return (free(new), NULL);
	return (new);
}
