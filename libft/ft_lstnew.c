/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:47:20 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 20:16:38 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ret_val;

	ret_val = NULL;
	ret_val = (t_list *)malloc(sizeof(t_list));
	if (!(ret_val))
		return (NULL);
	ret_val->content = NULL;
	ret_val->content_size = 0;
	if (content)
	{
		ret_val->content = malloc(sizeof(content));
		if (!(ret_val->content))
			return (NULL);
		ft_memcpy(ret_val->content, content, ft_strlen(content));
	}
	ret_val->next = NULL;
	return (ret_val);
}
