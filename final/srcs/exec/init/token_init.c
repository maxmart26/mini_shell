/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:14:38 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/09 18:01:31 by lnunez-t         ###   ########.fr       */
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
	strs = ft_split(tmp2, ' ');
	free(tmp2);
	return (strs);
}
