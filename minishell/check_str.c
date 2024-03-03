/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:19:22 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:23:04 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}

int	check_str(char *str)
{
	int		i;

	i = 0;
	if (!str[i])
	{
		return (-1);
	}
	if (check_str2(str) == -1)
		return (-1);
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (-1);
	if (ft_isalnum(str[i]) == -1 && str[i] != '/'
		&& str[i] != '\'' && str[i] != '\"' && str[i] != '.')
	{
		printf("Minishell : syntax error near unexpected token \'%c\'\n", str[i]);
		return (-1);
	}
	if (check_str3(str) == -1)
		return (-1);
	return (0);
}

int	check_str3(char *str)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	if (str[i])
	{
		while (str[i] && ft_isforbiden(str[i]) == -1)
			i++;
		while (str[i])
		{
			if (ft_isforbiden(str[i]) == 0)
				check = 1;
			i++;
		}
		if (check == 0)
			return (-1);
	}
	return (0);
}

int	check_str2(char *str)
{
	int		i;	

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (ft_isalnum(str[i]) == -1)
			{
				if (str[i] == '|')
				{
					printf("Minishell : Parse error near \'|\'\n");
					return (-1);
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	ft_isforbiden(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '(' || c == ')')
		return (-1);
	return (0);
}
