/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:53:22 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/11/28 17:53:32 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int i_haystack;
	int i_needle;

	i_haystack = 0;
	i_needle = 0;
	if (needle[i_needle] == '\0')
		return ((char *)haystack);
	while (haystack[i_haystack] && len--)
	{
		if (needle[i_needle] == '\0' && i_needle != 0)
			return ((char *)&haystack[i_haystack - i_needle]);
		if (haystack[i_haystack] == needle[i_needle])
			i_needle++;
		else if (haystack[i_haystack + 1] != '\0')
			i_needle = 0;
		i_haystack++;
	}
	if (haystack[i_haystack] == '\0' && needle[i_needle] == '\0')
		return ((char *)&haystack[i_haystack - i_needle]);
	return (NULL);
}
