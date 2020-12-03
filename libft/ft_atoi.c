/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:03:33 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/11/28 17:54:45 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int safety_ret_val;
	int i;
	int pos;

	pos = 1;
	i = 0;
	safety_ret_val = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			pos *= -1;
	while (str[i] <= '9' && str[i] >= '0')
	{
		safety_ret_val = safety_ret_val * 10 + (str[i++] - '0');
	}
	i = (safety_ret_val * pos);
	return (i);
}
