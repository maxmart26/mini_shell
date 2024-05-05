/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:27:35 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/05 18:35:45 by matorgue         ###   ########.fr       */
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
	else if (nbr < 10)
	{
		ft_putchar((nbr + '0'), len);
	}
}
