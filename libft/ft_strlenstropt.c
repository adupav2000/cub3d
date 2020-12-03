/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenstropt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:24:08 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/11/28 19:16:10 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlenstropt(const char *str, const char *set)
{
	size_t			ret_val;
	unsigned	int	i;

	i = 1;
	ret_val = ft_strlenopt(str, *set);
	while (*(set + i))
	{
		if (ret_val > ft_strlenopt(str, *(set + i)))
			ret_val = ft_strlenopt(str, *(set + i));
		i++;
	}
	return (ret_val);
}
