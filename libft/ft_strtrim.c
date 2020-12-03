/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:53:22 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/12/17 17:16:13 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*ret_val;
	unsigned int	i;
	unsigned int	i2;
	unsigned int	lim;

	if (s1 == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strnew(1));
	ret_val = NULL;
	i = 0;
	lim = 0;
	i2 = 0;
	while (ft_occures_in_set(s1[i], set) != -1 && s1[i])
		i++;
	lim = ft_strlen(s1);
	while (ft_occures_in_set(s1[lim - 1], set) != -1 && lim > i)
		lim--;
	return (ft_substr(s1, i, (lim - i)));
}
