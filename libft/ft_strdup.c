/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:53:22 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 20:59:32 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*to_allocate;
	int		i;

	i = ft_strlen(s1);
	to_allocate = ft_strnew(i);
	if (!(to_allocate))
		return (0);
	ft_memcpy(to_allocate, s1, i);
	to_allocate[ft_strlen(s1)] = '\0';
	return (to_allocate);
}
