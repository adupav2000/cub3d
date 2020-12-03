/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:12:11 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/11/28 19:17:24 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*s1;

	s1 = (char *)s;
	i = 0;
	while (s[i])
	{
		s1[i] = (char)malloc(1);
		s1[i] = (*f)(s1[i]);
		i++;
	}
	return (s1);
}
