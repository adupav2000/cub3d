/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountopt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:34:40 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/12/07 12:56:57 by adu-pavi         ###   ########.fr       */
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
