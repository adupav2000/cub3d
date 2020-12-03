/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:05:42 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/12/17 18:47:31 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = 0;
	if (!dst)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (--dstsize && src[i])
	{
		dst[i] = src[i];
		++i;
	}
	if (dst[i] != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}
