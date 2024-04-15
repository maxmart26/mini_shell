/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:15:15 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/10 18:27:18 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_strl_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	conv_base_error(unsigned long nbr, char *base, unsigned int len_base,
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
			conv_base_error(div, base, len_base, len);
			conv_base_error(mod, base, len_base, len);
		}
	}
	else
		ft_putchar_error(base[nbr % len_base], len);
}

void	ft_putnbr_base_error(unsigned long nbr, char *base, int *len)
{
	int	len_base;

	len_base = ft_strl_error(base);
	conv_base_error(nbr, base, len_base, len);
}
