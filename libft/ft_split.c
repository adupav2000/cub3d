/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:09:47 by adu-pavi          #+#    #+#             */
/*   Updated: 2019/12/18 23:58:43 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_get_tab(char const *s, char c)
{
	int		i;
	int		segement;
	char	**tab;

	segement = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			segement++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	if (!(tab = malloc(sizeof(*tab) * (segement + 1))))
		return (0);
	tab[segement] = 0;
	return (tab);
}

static char		*ft_fill_tab(char const *s, char c, char *tab, int i)
{
	int		index;

	index = 0;
	while (s[i] && s[i] != c)
	{
		tab[index] = s[i];
		index++;
		i++;
	}
	return (tab);
}

static int		ft_get_segement(char const *s, char c, int *i)
{
	int		segement;

	segement = 0;
	while (s[*i] && s[*i] != c)
	{
		segement++;
		*i = *i + 1;
	}
	return (segement);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		line;
	int		segement;
	char	**tab;

	if (!s)
		return (0);
	if (!(tab = ft_get_tab(s, c)))
		return (0);
	i = 0;
	line = -1;
	while (s[i])
	{
		if (s[i] != c)
		{
			segement = ft_get_segement(s, c, &i);
			if (!(tab[++line] = malloc(sizeof(**tab) * (segement + 1))))
				return (0);
			tab[line] = ft_fill_tab(s, c, tab[line], i - segement);
			tab[line][segement] = '\0';
		}
		else
			i++;
	}
	return (tab);
}

// #include "libft.h"

// size_t	ft_split_get_len_til_next(char const *str, char lock)
// {
// 	size_t ret_val;

// 	ret_val = 0;
// 	while (str[ret_val] != lock && str[ret_val])
// 		ret_val++;
// 	return (ret_val);
// }

// char	*ft_split_get_str(char const *str, char lock)
// {
// 	size_t	i;
// 	char	*ret_val;

// 	i = 0;
// 	ret_val = NULL;
// 	while (str[i] != lock && str[i])
// 	{
// 		i++;
// 		ret_val[i] = str[i];
// 	}
// 	return (ret_val);
// }

// size_t	ft_split_count_words(char const *str, char lock)
// {
// 	size_t i;
// 	size_t ret_val;

// 	ret_val = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != lock)
// 		{
// 			while (str[i] != lock && str[i])
// 				i++;
// 			ret_val++;
// 		}
// 		while (str[i] == lock)
// 			i++;
// 	}
// 	return (ret_val);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**ret_val;
// 	size_t	i;
// 	size_t	i2;

// 	if (!s)
// 		return (0);
// 	i = 0;
// 	i2 = 0;
// 	ret_val = NULL;
// 	if (!(ret_val = malloc(sizeof(char *) * ft_split_count_words(s, c))))
// 		return (0);
// 	while (s[i] != 0)
// 	{
// 		while (s[i] == c)
// 			i++;
// 		ret_val[i2] = ft_substr(&s[i], 0,
// 			ft_split_get_len_til_next(&s[i], c));
// 		i += ft_split_get_len_til_next(&s[i], c);
// 		while (s[i] == c)
// 			i++;
// 		i2++;
// 	}
// 	ret_val[i2] = NULL;
// 	return (ret_val);
// }
