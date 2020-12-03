/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_occure_in_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:25:11 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/12/07 13:21:08 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_occures_in_set(char c, char const *set)
{
	int i;

	i = 0;
	while (*(set + i) && *(set + i) != c)
		i++;
	if (!*(set + i))
		return (-1);
	else
		return (i);
}
