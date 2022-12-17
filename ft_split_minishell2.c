/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:00:26 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:02:29 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_gestion_less_quote_malloc_words(char *s, size_t *compt,
		size_t (*i), char sep)
{
	while ((s)[*i] && !((s[*i] >= 9 && s[*i] <= 13)
		|| s[*i] == sep) && s[*i] != '\"' && s[*i] != '\'')
	{
		*i += 1;
		*compt += 1;
	}
}

void	ft_gestion_space_malloc_words(char *s,
		size_t (*i), char sep)
{
	while (s[(*i)] && (((s[(*i)] >= 9 && s[(*i)] <= 13)
				|| s[(*i)] == sep) || s[(*i)] == sep))
		(*i) += 1;
}

void	ft_malloc_words2(char ***tab, size_t *j, size_t *compt, size_t *compt2)
{
	(*tab)[(*j)] = malloc(sizeof(char) * ((*compt) + (*compt2) + 1));
	if (!(*tab)[(*j)])
		return ;
	(*tab)[(*j)][(*compt) + (*compt2)] = '\0';
	(*compt) = 0;
	(*compt2) = 0;
	(*j) += 1;
}

char	**ft_malloc_words_minishell(char *s, char **tab, size_t nbline
		, char sep)
{
	size_t	i;
	size_t	j;
	size_t	compt;
	size_t	compt2;
	int		variable;

	compt = 0;
	compt2 = 0;
	j = 0;
	i = 0;
	while (s[i] && j < nbline)
	{
		variable = 0;
		ft_gestion_space_malloc_words(s, &i, sep);
		ft_gestion_quote_malloc_words(s, &compt, &i, '\"');
		ft_gestion_less_quote_malloc_words(s, &compt, &i, sep);
		ft_gestion_quote_malloc_words(s, &compt2, &i, '\'');
		if (!s[i] || (s[i] && (compt + compt2 > 0
					&& ((s[i] >= 9 && s[i] <= 13) || s[i] == sep))))
		{
			ft_malloc_words2(&tab, &j, &compt, &compt2);
		}
	}
	return (tab);
}

char	**ft_malloc_tab2d_minishell(char *s, char sep)
{
	size_t	nbline;
	char	**tab;

	nbline = ft_nbwords_minishell(s, sep);
	if (s[0] == '\0' || nbline == 0)
	{
		tab = (char **)malloc(sizeof(char *) * 2);
		if (!tab)
			return (0);
		tab[0] = 0;
		return (tab);
	}
	tab = (char **)malloc(sizeof(char *) * (nbline + 1));
	tab[nbline] = NULL;
	if (!tab)
		return (NULL);
	tab = ft_malloc_words_minishell(s, tab, nbline, sep);
	if (!tab)
		return (NULL);
	return (tab);
}
