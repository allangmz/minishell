/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:12:59 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/16 15:15:49 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	gestion_quote_nbwords(char *s, size_t *i)
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

static int	ft_nbwords_minishell(char *s, char sep)
{
	size_t	i;
	size_t	nbline;

	if (s[0] == '\0')
		return (0);
	i = 0;
	nbline = 1;
	while (s[i])
	{
		while (s[i] && (((s[i] >= 9 && s[i] <= 13)) || s[i] == sep) )
		{
			i++;
		}
		if (s[i] == '\0')
			nbline --;
		gestion_quote_nbwords(s, &i);
		while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == sep) && s[i] != '\"' && s[i] != '\'')
			i++;
		if (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == sep) || s[i] == sep || s[i] != '\'' || s[i] != '\"'))
		{
			nbline++;
		}
	}
	return (nbline);
}

void	ft_gestion_quote_malloc_words(char *s, size_t *compt, size_t (*i), char quote)
{
	if (s[(*i)] && s[(*i)] == quote)
	{
		(*i) += 1;
		while (s[(*i)] && s[(*i)] != quote)
		{
			(*i) += 1;
			compt += 1;
		}
		(*i) += 1;
	}
}

char	**ft_malloc_words_minishell(char *s, char **tab, size_t nbline, char sep)
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
		while (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == sep) || s[i] == sep) )
			i++;
		ft_gestion_quote_malloc_words(s, &compt, &i, '\"');
		while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == sep) && s[i] != '\"' && s[i] != '\'')
		{
			i++;
			compt++;
		}
		ft_gestion_quote_malloc_words(s, &compt2, &i, '\'');
		if (compt + compt2 > 0 && ((((s[i] >= 9 && s[i] <= 13) || s[i] == sep) || s[i] == sep)  || !s[i]))
		{
			tab[j] = malloc(sizeof(char) * (compt + compt2 + 1));
			if (!tab[j])
				return (NULL); // faut tout free;
			tab[j][compt + compt2] = '\0';
			compt = 0;
			compt2 = 0;
			j++;
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

char	**ft_split_minishell(char *s, char sep)
{
	size_t	i;
	size_t	index[2];
	char	**tab;

	if (!s)
		return (0);
	tab = ft_malloc_tab2d_minishell(s, sep);
	if (!tab)
		return (0); // faut faire quelque chose (dire qu'il y a une erreur)
	i = 0;
	index[0] = 0;
	index[1] = 0;
	while (tab[index[0]] && s[i])
	{
		while (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == sep) || s[i] == sep) )
		{
			i++;
		}
		while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == sep) && s[i] != '\"' && s[i] != '\'')
		{
			tab[index[0]][index[1]] = s[i];
			index[1]++;
			i++;
		}
		if (s[i] && s[i] == '\"')
		{
			i ++;
			while (s[i] && s[i] != '\"')
			{
				tab[index[0]][index[1]] = s[i];
				i++;
				index[1]++;
			}
			i++;
		}
		if (s[i] && s[i] == '\'')
		{
			i ++;
			while (s[i] && s[i] != '\'')
			{
				tab[index[0]][index[1]] = s[i];
				i++;
				index[1]++;
			}
			i++;
		}
		if (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == sep) || s[i] == sep))
		{
			tab[index[0]][index[1]] = '\0';
			index[0] += 1;
			index[1] = 0;
		}
	}
	// tab[index[0]][index[1]] = '\0';
	return (tab);
}

int	ft_size_variable(char *str)
{
	int	i;

	i = 0;
	i++;
	while (str[i] && (ft_isalnum(str[i]) == 0 || str[i] == '_'))
	{
		i++;
	}
	return (i);
}

static void ft_replace_variable(char **str, int *i, char *env[])
{
	char	*char_last_return;

	if ((*str)[(*i)] && (*str)[(*i) + 1] == '?')
	{
		char_last_return = ft_itoa(LAST_RETURN);
		(*str) = ft_expand_last_return(str, char_last_return,
				(*i), ft_strlen(char_last_return));
	}
	else if ((*str)[(*i)] && (ft_isalnum((*str)[(*i) + 1]) == 0
				|| (*str)[(*i) + 1] == '_'))
	{
		(*str) = ft_expand_string_variables(str, env,
				(*i), ft_size_variable((*str) + (*i)));
	}
}

static void ft_gestion_double_quote(char **str, int *i, char *env[])
{
	if ((*str)[(*i)] && (*str)[(*i)] == '\"')
	{	
		(*i) += 1;
		while ((*str)[(*i)] && (*str)[(*i)] != '\"')
		{
			if ((*str)[(*i)] && (*str)[(*i)] == '$')
			{
				ft_replace_variable(str, i, env);
			}
			(*i) += 1;
		}
		(*i) += 1;
	}
	return ;
}

static void ft_gestion_any_quote(char **str, int *i, char *env[])
{
	while ((*str)[(*i)] && !(((*str)[(*i)] >= 9 && (*str)[(*i)] <= 13)
		|| (((*str)[(*i)] >= 9 && (*str)[(*i)] <= 13)
				|| (*str)[(*i)] == ' ')) && (*str)[(*i)] != '\"'
					&& (*str)[(*i)] != '\'')
	{
		if ((*str)[(*i)] && (*str)[(*i)] == '$')
		{
			ft_replace_variable(str, i, env);
		}
		(*i) += 1;
	}
}

// traduit les variables par leur traduction
char	*translate_variable(char *str, char *env[])
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
			i++;
		if (str[i] == '\0')
			break ;
		ft_gestion_double_quote(&str, &i, env);
		ft_gestion_any_quote(&str, &i, env);
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
	}
	return (str);
}
