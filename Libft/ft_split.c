/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:29:23 by aguemazi          #+#    #+#             */
/*   Updated: 2022/07/26 11:16:55 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbwords(char const *s, char c)
{
	size_t	i;
	size_t	nbline;

	if (s[0] == '\0')
		return (0);
	i = 0;
	while (s[i] == c && s[i])
		i++;
	nbline = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c && s[i - 1] != c)
			nbline++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c)
		nbline++;
	return (nbline);
}

char	**ft_malloc_words(char const *s, char c, char **tab, size_t nbline)
{
	size_t	i;
	size_t	j;
	size_t	compt;

	tab[nbline] = 0;
	j = 0;
	i = 0;
	while (s[i] && j < nbline)
	{
		while (s[i] == c && s[i])
			i++;
		compt = 0;
		while (s[i] != c && s[i++])
			compt ++;
		if (s[i - 1] != c)
		{
			tab[j] = malloc(sizeof(char) * (compt + 1));
			if (!tab)
				return (0);
			tab[j][compt] = '\0';
		}
		j++;
	}
	return (tab);
}

char	**ft_malloc_tab2d(char const *s, char c)
{
	size_t	nbline;
	char	**tab;

	nbline = ft_nbwords(s, c);
	if (s[0] == '\0' || nbline == 0)
	{
		tab = (char **)malloc(sizeof(char *) * 2);
		if (!tab)
			return (0);
		tab[0] = 0;
		return (tab);
	}
	tab = (char **)malloc(sizeof(char *) * (nbline + 1));
	if (!tab)
		return (0);
	tab = ft_malloc_words(s, c, tab, nbline);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	index[2];
	char	**tab;

	if (!s)
		return (0);
	tab = ft_malloc_tab2d(s, c);
	if (!tab)
		return (0);
	i = 0;
	index[0] = 0;
	while (tab[index[0]] && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		index[1] = 0;
		while (s[i] != c && s[i])
		{
			tab[index[0]][index[1]] = s[i];
			index[1]++;
			i++;
		}
		index[0]++;
	}
	return (tab);
}
