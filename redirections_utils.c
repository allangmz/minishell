/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:27:53 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 21:54:13 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return l'index de la 1ere redirection
int	redirection_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (i > 0 && (str[i] == '<' || str[i] == '>'))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isalnum(int c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97)
		|| (c >= 48 && c <= 57) || c == ' ')
		return (0);
	return (-1);
}

int	ft_test(char *str, int i)
{
	if (i > 0 && (str[i + 1] != str[i] && ft_isalnum(str[i + 1]) == -1))
	{
		printf("Minishell : syntax error near unexpected token '%c'\n", str[i]);
		return (-1);
	}
	return (0);
}

int	ft_pick_redirection(char *str)
{
	int	i;
	int	redirection;

	i = 0;
	if (str[i] == '>')
	{
		redirection = 1;
		i++;
		if (str[i] == '>')
		{
			redirection = 2;
		}
	}
	if (str[i] == '<')
	{
		redirection = 3;
		i++;
		if (str[i] == '<')
		{
			redirection = 4;
		}
	}
	return (redirection);
}

void	ft_gestion_quote_count(char *str, int *i)
{
	if (str[*i] && str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\'')
		{
			*i += 1;
		}
		*i += 1;
	}
	if (str[*i] && str[*i] == '\"')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\"')
		{
			*i += 1;
		}
		*i += 1;
	}
}
