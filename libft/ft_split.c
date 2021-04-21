/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:09:47 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/21 13:07:34 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_get_tab(char const *s, char c)
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
	tab = malloc(sizeof(*tab) * (segement + 1));
	if (!(tab))
		return (0);
	tab[segement] = 0;
	return (tab);
}

static char	*ft_fill_tab(char const *s, char c, char *tab, int i)
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

static int	ft_get_segement(char const *s, char c, int *i)
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

char		**ft_split(char const *s, char c)
{
	int		i;
	int		line;
	int		segement;
	char	**tab;

	tab = ft_get_tab(s, c);
	if (!(tab) || !s)
		return (0);
	i = 0;
	line = -1;
	while (s[i])
	{
		if (s[i] != c)
		{
			segement = ft_get_segement(s, c, &i);
			tab[++line] = malloc(sizeof(**tab) * (segement + 1));
			if (!(tab[line]))
				return (0);
			tab[line] = ft_fill_tab(s, c, tab[line], i - segement);
			tab[line][segement] = '\0';
		}
		else
			i++;
	}
	return (tab);
}
