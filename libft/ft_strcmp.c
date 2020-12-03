/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:10:02 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/12/07 13:10:33 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int ret_val;
	int prog;

	prog = 0;
	ret_val = 0;
	while (s1[prog] == s2[prog] && s1[prog])
		prog++;
	ret_val = (int)(s1[prog] - s2[prog]);
	return (ret_val);
}
