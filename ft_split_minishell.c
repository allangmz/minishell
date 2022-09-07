/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:12:59 by aguemazi          #+#    #+#             */
/*   Updated: 2022/08/25 14:39:16 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_nbwords_minishell(char *s)
{
	size_t	i;
	size_t	nbline;

	if (s[0] == '\0')
		return (0);
	i = 0;
	nbline = 1;
	while (s[i])
	{
		while (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') || s[i] == ' ') )
		{
			i++;
		}
		if (s[i] == '\0')
			nbline --;
		if (s[i] && s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
			{
				i++;
			}
			i++;
		}
		if (s[i] && s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
			{
				i++;
			}
			i++;
		}
		while (!((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') && s[i] != '\"' && s[i] != '\'' && s[i])
			i++;
		if (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') || s[i] == ' ') )
		{
			nbline++;
		}
	}
	return (nbline);
}

char	**ft_malloc_words_minishell(char *s, char **tab, size_t nbline)
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
		while (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') || s[i] == ' ') )
		{
			i++;
		}
		if (s[i] && s[i] == '\"')
		{
			i ++;
			while (s[i] && s[i] != '\"')
			{
				i++;
				compt++;
			}
			i++;
		}
		while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') && s[i] != '\"' && s[i] != '\'')
		{
			i++;
			compt++;
		}
		if (s[i] == '\'')
		{
			i ++;
			while (s[i] && s[i] != '\'')
			{
				i++;
				compt2++;
			}
			i++;
		}
		if (compt + compt2 > 0 && ((((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') || s[i] == ' ')  || !s[i]))
		{
			tab[j] = malloc(sizeof(char) * (compt + compt2 + 1));
			if (!tab[j])
			{
				return (NULL); // faut tout free;
			}
			tab[j][compt + compt2] = '\0';
			compt = 0;
			compt2 = 0;
			j++;
		}
	}
	return (tab);
}

char	**ft_malloc_tab2d_minishell(char *s)
{
	size_t	nbline;
	char	**tab;

	nbline = ft_nbwords_minishell(s);
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
		return (0);
	tab = ft_malloc_words_minishell(s, tab, nbline);
	return (tab);
}

char	**ft_split_minishell(char *s)
{
	size_t	i;
	size_t	index[2];
	char	**tab;

	if (!s)
		return (0);
	tab = ft_malloc_tab2d_minishell(s);
	if (!tab)
		return (0); // faut faire quelque chose (dire qu'il y a une erreur)
	i = 0;
	index[0] = 0;
	index[1] = 0;
	while (tab[index[0]] && s[i])
	{
		while (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') || s[i] == ' ') )
		{
			i++;
		}
		while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') && s[i] != '\"' && s[i] != '\'')
		{
			tab[index[0]][index[1]] = s[i];
			index[1]++;
			i++;
		}
		if (s[i] && s[i] == '\"')
		{
			i ++;
			while (s[i] != '\"')
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
			while (s[i] != '\'')
			{
				tab[index[0]][index[1]] = s[i];
				i++;
				index[1]++;
			}
			i++;
		}
		if (s[i] && (((s[i] >= 9 && s[i] <= 13) || s[i] == ' ') || s[i] == ' '))
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
	while (str[i] && ft_isalnum(str[i]))
	{
		i++;
	}
	return (i);
}

char	*test(char *str, char *env[], int last_return)
{
	int		i;
	char	*char_last_return;

	i = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		{
			i++;
		}
		if (str[i] == '\0')
			break ;
		if (str[i] && str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
				{
					if (str[i + 1] == '?')
					{
						char_last_return = ft_itoa(last_return);
						str = ft_expand_last_return(str, char_last_return, i, ft_strlen(char_last_return));
					}
					else if (!ft_isalnum(str[i + 1]))
						str = ft_expand_string_variables(str, env, i, ft_size_variable(str + i));
				}
				else
					i++;
			}
			i++;
		}
		while (!((str[i] >= 9 && str[i] <= 13) || ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')) && str[i] != '\"' && str[i] != '\'' && str[i])
		{
			if (str[i] == '$')
			{
				if (str[i + 1] == '?')
				{
					char_last_return = ft_itoa(last_return);
					str = ft_expand_last_return(str, char_last_return, i, ft_strlen(char_last_return));
				}
				else if (ft_isalnum(str[i + 1]))
					str = ft_expand_string_variables(str, env, i, ft_size_variable(str + i));
			}
			i++;
		}
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				i++;
			}
			i++;
		}
	}
	return (str);
}

// int main(int argc, char **argv,char *env[])
// {
// 	char	*test1 = "echo 'test'$HOME";
// 	char	**oi;

// 	(void) argv;
// 	(void) argc;
// 	test1 = test(test1, env, last_return);
// 	oi = ft_split_minishell(test1);
// 	ft_exec_path(oi, env);
// 	ft_free_doublechar(&oi);
// 	free(test1);
// 	system("leaks minishel");
// }


// faut trouver pourquooi echo sd$HOME'test'$PATH ca marche pas c''est pas normal