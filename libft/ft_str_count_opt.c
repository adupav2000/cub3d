/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_count_opt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:02:47 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/12/07 13:20:15 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned	int	ft_str_count_opt(char *str, char c)
{
	int i;
	int ret_val;

	i = 0;
	ret_val = 0;
	while (str[i])
		if (c == str[i++])
			ret_val++;
	return (ret_val);
}
