/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:00:05 by lnunez-t          #+#    #+#             */
/*   Updated: 2023/11/13 11:35:17 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_n(long n)
{
	size_t	size;

	size = 0;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*dest;
	long int	num;
	size_t		size;
	size_t		is_negative;

	num = n;
	size = size_n(num);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	is_negative = 0;
	if (num < 0)
	{
		dest[0] = '-';
		num *= -1;
		is_negative = 1;
	}
	dest[size] = '\0';
	while (size > is_negative)
	{
		dest[size - 1] = num % 10 + '0';
		num /= 10;
		size--;
	}
	return (dest);
}
