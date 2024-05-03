/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_un_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:52:31 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/02 18:30:05 by lnunez-t         ###   ########.fr       */
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
	else if (nbr < 10)// && nbr >= 0)
	{
		ft_putchar_error((nbr + '0'), len);
	}
}
