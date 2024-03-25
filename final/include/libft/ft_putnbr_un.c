/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:27:35 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/01/19 18:11:29 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_un(unsigned long nbr, int *len)
{
	if (nbr > 9)
	{
		ft_putnbr_un((nbr / 10), len);
		ft_putnbr_un((nbr % 10), len);
	}
	else if (nbr < 10 && nbr >= 0)
	{
		ft_putchar((nbr + '0'), len);
	}
}
