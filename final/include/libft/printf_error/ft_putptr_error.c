/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:24:34 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/10 18:25:54 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"


void	ft_putptr_error(void *p, int *len)
{
	if (p == NULL)
	{
		write(2, "(nil)", 5);
		(*len) += 5;
		return ;
	}
	ft_putstr_error("0x", len);
	ft_putnbr_base_error((unsigned long) p, HEX_LOW_FMT, len);
}
