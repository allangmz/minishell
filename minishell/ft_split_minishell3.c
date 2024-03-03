/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:03:00 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 21:52:58 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gestion_quote_nbwords(char *s, size_t *i)
{
	if (s[*i] && s[*i] == '\"')
	{
		*i += 1;
		while (s[*i] && s[*i] != '\"')
		{
			*i += 1;
		}
		*i += 1;
	}
	else if (s[*i] && s[*i] == '\'')
	{
		*i += 1;
		while (s[*i] && s[*i] != '\'')
		{
			*i += 1;
		}
		*i += 1;
	}
	return ;
}

int	ft_nbwords_minishell(char *s, char sep)
{
	size_t	i;
	size_t	nbline;

	if (s[0] == '\0')
		return (0);
	i = 0;
	nbline = 1;
	while (s[i])
	{
		while (s[i] && (((s[i] >= 9 && s[i] <= 13)) || s[i] == sep))
			i++;
		if (s[i] == '\0')
			nbline --;
		gestion_quote_nbwords(s, &i);
		while (s[i] && !((s[i] >= 9 && s[i] <= 13)
				|| s[i] == sep) && s[i] != '\"' && s[i] != '\'')
			i++;
		if (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == sep)
				|| s[i] == sep || s[i] != '\'' || s[i] != '\"'))
			nbline++;
	}
	return (nbline);
}

void	ft_gestion_quote_malloc_words(char *s, size_t *compt,
		size_t (*i), char quote)
{
	if (s[(*i)] && s[(*i)] == quote)
	{
		(*i) += 1;
		while (s[(*i)] && s[(*i)] != quote)
		{
			(*i) += 1;
			*compt += 1;
		}
		(*i) += 1;
	}
}

void	ft_gestion_quote_split(char *s, char ***tab,
			size_t *i, size_t (*index)[2])
{
	if (s[*i] && s[*i] == '\"')
	{
		*i += 1;
		while (s[*i] && s[*i] != '\"')
		{
			(*tab)[(*index)[0]][(*index)[1]] = s[*i];
			*i += 1;
			(*index)[1] += 1;
		}
		*i += 1;
	}
	if (s[*i] && s[*i] == '\'')
	{
		*i += 1;
		while (s[*i] && s[*i] != '\'')
		{
			(*tab)[(*index)[0]][(*index)[1]] = s[*i];
			*i += 1;
			(*index)[1] += 1;
		}
		*i += 1;
	}
	return ;
}

void	ft_norminette_est_relou(char *s, size_t *i,
	char ***tab, size_t (*index)[2])
{
	while (s[(*i)] && (((s[(*i)] >= 9 && s[(*i)] <= 13) || s[(*i)] == ' ')
			|| s[(*i)] == ' '))
		(*i)++;
	while (s[(*i)] && !((s[(*i)] >= 9 && s[(*i)] <= 13) || s[(*i)] == ' ')
		&& s[(*i)] != '\"' && s[(*i)] != '\'')
	{
		(*tab)[(*index)[0]][(*index)[1]] = s[(*i)];
		(*index)[1] += 1;
		(*i) += 1;
	}
}
