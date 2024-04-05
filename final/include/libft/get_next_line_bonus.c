/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:50:41 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/25 16:11:03 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_line(char *stockage)
{
	int	i;

	if (stockage == NULL)
		return (0);
	i = 0;
	while (stockage[i])
	{
		if (stockage[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_clean(char *stockage, int i, int j)
{
	char	*str;

	if (stockage[0] == '\0')
	{
		free(stockage);
		return (NULL);
	}
	while (stockage[i] && stockage[i] != '\n')
		i++;
	str = malloc((ft_strlen(stockage) - i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (stockage[i] != '\0')
		i++;
	while (stockage[i])
	{
		str[j] = stockage[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(stockage);
	return (str);
}

char	*ft_remplissage(int fd, char *stockage)
{
	char	*buffer;
	int		size;

	size = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (ft_check_line(stockage) == 0 && size > 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size < 0 || (size == 0 && stockage == NULL))
		{
			free(buffer);
			return (NULL);
		}
		buffer[size] = '\0';
		stockage = ft_strjoin(stockage, buffer);
		if (stockage == NULL)
			return (NULL);
	}
	free(buffer);
	return (stockage);
}

char	*get_next_line(int fd)
{
	static char	*stockage[10000];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stockage[fd] = ft_remplissage(fd, stockage[fd]);
	if (stockage[fd] == NULL)
		return (NULL);
	line = ft_cut(stockage[fd]);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	stockage[fd] = ft_clean(stockage[fd], 0, 0);
	return (line);
}
