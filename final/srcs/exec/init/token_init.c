/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:14:38 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/15 13:06:55 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

char	**token_init(char *str, char *st)
{
	char	*tmp;
	char	*tmp2;
	char	**strs;

	tmp = ft_strjoin(str, " ");
	tmp2 = ft_strjoin(tmp, st);
	free(tmp);
	//free(st);
	strs = ft_split(tmp2, ' ');
	free(tmp2);
	return (strs);
}
