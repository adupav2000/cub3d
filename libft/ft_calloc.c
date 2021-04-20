/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:56:12 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 20:59:10 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret_val;

	if (count <= 0)
		count = 1;
	if (size <= 0)
		size = 1;
	ret_val = 0;
	if (count == 0 || size == 0)
		return (0);
	ret_val = malloc(size * count);
	if (!(ret_val))
		return (NULL);
	ft_bzero(ret_val, size * count);
	return (ret_val);
}
