/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:26:19 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/11/28 18:32:46 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	safe_stock;
	int			diviser;

	safe_stock = n;
	diviser = 1000000000;
	if (safe_stock < 0)
	{
		safe_stock = -safe_stock;
		ft_putchar_fd('-', fd);
	}
	while (!(safe_stock / diviser) && diviser != 1)
		diviser = diviser / 10;
	while (diviser != 0)
	{
		ft_putchar_fd(((safe_stock / diviser) + 48), fd);
		safe_stock -= (safe_stock / diviser) * diviser;
		diviser = diviser / 10;
	}
}
