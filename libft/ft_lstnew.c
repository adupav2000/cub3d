/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:47:20 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/12/17 17:13:49 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ret_val;

	ret_val = NULL;
	if (!(ret_val = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	ret_val->content = NULL;
	ret_val->content_size = 0;
	if (content)
	{
		if (!(ret_val->content = malloc(sizeof(content))))
			return (NULL);
		ft_memcpy(ret_val->content, content, ft_strlen(content));
	}
	ret_val->next = NULL;
	return (ret_val);
}
