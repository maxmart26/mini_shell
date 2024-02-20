/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:16:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/20 18:26:58 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"

int	main(void)
{
	t_token	*list;
	char	*str;

	while (1)
	{
		str = readline("matorgue:~$ ");
		list = lexer(str);
		printf("%s", list->next->next->next->next->next->value);
	}
	return (0);
}
