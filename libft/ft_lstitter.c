/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstitter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:30:37 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 20:49:34 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstitter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	ptr = lst->next;
	(*f)(lst);
	while (lst->next)
	{
		ptr = lst->next;
		(*f)(lst);
		lst = ptr;
	}
	free(ptr);
}
