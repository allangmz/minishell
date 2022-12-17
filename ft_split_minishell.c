/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:12:59 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 21:53:59 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_minishell(char *s, char sep)
{
	size_t	i;
	size_t	index[2];
	char	**tab;

	if (!s)
		return (0);
	tab = ft_malloc_tab2d_minishell(s, sep);
	if (!tab)
		return (0);
	i = 0;
	index[0] = 0;
	index[1] = 0;
	while (tab[index[0]] && s[i])
	{
		ft_norminette_est_relou(s, &i, &tab, &index);
		ft_gestion_quote_split(s, &tab, &i, &index);
		if (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == sep) || s[i] == sep))
		{
			tab[index[0]][index[1]] = '\0';
			index[0] += 1;
			index[1] = 0;
		}
	}
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

void	ft_replace_variable(char **str, int *i, char *env[])
{
	char	*char_last_return;

	if ((*str)[(*i)] && (*str)[(*i) + 1] == '?')
	{
		char_last_return = ft_itoa(g_last_return);
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

void	ft_gestion_double_quote(char **str, int *i, char *env[])
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
			else
				(*i) += 1;
		}
		(*i) += 1;
	}
	return ;
}

void	ft_gestion_any_quote(char **str, int *i, char *env[])
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
