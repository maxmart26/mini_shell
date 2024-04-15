/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_un_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:52:31 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/10 18:27:28 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_un_error(unsigned long nbr, int *len)
{
	if (nbr > 9)
	{
		ft_putnbr_un_error((nbr / 10), len);
		ft_putnbr_un_error((nbr % 10), len);
	}
	else if (nbr < 10 && nbr >= 0)
	{
		ft_putchar_error((nbr + '0'), len);
	}
}
