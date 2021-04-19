/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:57:25 by AlainduPavi       #+#    #+#             */
/*   Updated: 2019/11/28 18:21:08 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoa_2(char *str, int len, int nbr)
{
	*(str + len--) = '\0';
	while (nbr > 0)
	{
		*(str + len--) = nbr % 10 + '0';
		nbr /= 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	if (len == 0 && str[1] != '\0')
		*(str + len) = '-';
}

char	*ft_itoa(int n)
{
	long	nbr;
	size_t	len;
	char	*str;

	nbr = n;
	len = 1;
	if (nbr > 0)
		len = 0;
	if (nbr < 0)
		nbr = -nbr;
	while (n)
	{
		len++;
		n = n / 10;
	}
	str = (char *)malloc(sizeof(str) * len + 1);
	if (!str)
		return (NULL);
	ft_itoa_2(str, len, nbr);
	return (str);
}
