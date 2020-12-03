/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:56:12 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/11/28 17:06:39 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret_val;
	size_t	i;

	i = 0;
	count = count <= 0 ? 1 : count;
	size = size <= 0 ? 1 : size;
	ret_val = 0;
	if (count == 0 || size == 0)
		return (0);
	if (!(ret_val = malloc(size * count)))
		return (NULL);
	ft_bzero(ret_val, size * count);
	return (ret_val);
}
