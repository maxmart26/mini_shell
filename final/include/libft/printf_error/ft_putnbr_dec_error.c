/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_dec_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:22:40 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/10 18:27:22 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_dec_error(int nbr, int *len)
{
	if (nbr == -2147483648)
	{
		write(2, "-2147483648", 11);
		(*len) += 11;
		return ;
	}
	else if (nbr < 0)
	{
		ft_putchar_error('-', len);
		ft_putnbr_dec_error(-nbr, len);
	}
	else if (nbr > 9)
	{
		ft_putnbr_dec_error((nbr / 10), len);
		ft_putnbr_dec_error((nbr % 10), len);
	}
	else if (nbr < 10 && nbr >= 0)
	{
		ft_putchar_error((nbr + '0'), len);
	}
}
