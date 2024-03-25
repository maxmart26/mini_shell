/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:21:19 by lnunez-t          #+#    #+#             */
/*   Updated: 2023/11/14 18:21:31 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	conv_base(unsigned long nbr, char *base, unsigned int len_base,
		int *len)
{
	unsigned long	div;
	unsigned long	mod;

	if (nbr >= len_base)
	{
		if (nbr > 0)
		{
			div = nbr / len_base;
			mod = nbr % len_base;
			conv_base(div, base, len_base, len);
			conv_base(mod, base, len_base, len);
		}
	}
	else
		ft_putchar(base[nbr % len_base], len);
}

void	ft_putnbr_base(unsigned long nbr, char *base, int *len)
{
	int	len_base;

	len_base = ft_strl(base);
	conv_base(nbr, base, len_base, len);
}
