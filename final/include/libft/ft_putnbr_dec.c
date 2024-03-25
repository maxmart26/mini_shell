/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:37:30 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/01/19 18:11:25 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_dec(int nbr, int *len)
{
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) += 11;
		return ;
	}
	else if (nbr < 0)
	{
		ft_putchar('-', len);
		ft_putnbr_dec(-nbr, len);
	}
	else if (nbr > 9)
	{
		ft_putnbr_dec((nbr / 10), len);
		ft_putnbr_dec((nbr % 10), len);
	}
	else if (nbr < 10 && nbr >= 0)
	{
		ft_putchar((nbr + '0'), len);
	}
}
