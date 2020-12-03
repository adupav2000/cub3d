/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:03:13 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/11/28 17:46:09 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int i;

	i = 0;
	while (*(s + i))
		if (*(s + i++) == (char)c)
			return ((char *)(s + --i));
	if (*(s + i) == (char)c)
		return ((char *)(s + i));
	return (NULL);
}
