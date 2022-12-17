/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_string_variables.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:30:07 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 21:06:24 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_in_env(char *env[], char *variable)
{
	int	indice_variable;
	int	i;

	indice_variable = ft_get_indice_variable(env, variable);
	if (indice_variable == -1)
	{
		return (NULL);
	}
	i = 0;
	while (env[indice_variable][i] && env[indice_variable][i] != '=')
	{
		i++;
	}
	i++;
	free(variable);
	variable = env[indice_variable] + i;
	return (variable);
}

char	*ft_add_variable(char **str, int i, int j, char *env[])
{
	char	*variable;

	variable = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(variable, (*str) + i - j, j + 1);
	variable = get_variable_in_env(env, variable);
	(*str) = ft_delete_nchar(str, i - (j + 1), j + 1);
	if (variable)
		(*str) = ft_add_str_in_str(str, variable, i - j - 1);
	return (*str);
}

/*	n = number of char to browse 
	n < 0 -> all the string
*/
char	*ft_expand_string_variables(char **str,
	char *env[], size_t begin, size_t n)
{
	size_t	i;
	size_t	j;

	if (begin < 0)
		return ((*str));
	i = begin;
	while ((*str)[i] && i < begin + n)
	{
		if ((*str)[i] == '$')
		{
			i++;
			j = 0;
			while ((*str)[i] && (ft_isalnum((*str)[i]) == 0
					|| (*str)[i] == '_'))
			{
				i++;
				j++;
			}
			(*str) = ft_add_variable(str, i, j, env);
		}
		else
			i++;
	}
	return ((*str));
}

char	*ft_add_last_return(char **str, int i, char *char_last_return)
{
	(*str) = ft_delete_nchar(str, i - 1, 2);
	(*str) = ft_add_str_in_str(str, char_last_return, i - 1);
	return (*str);
}

char	*ft_expand_last_return(char **str, char *char_last_return,
		size_t begin, size_t n)
{
	size_t	i;

	if (begin < 0)
	{
		return (*str);
	}
	i = begin;
	while ((*str)[i] && i < begin + n)
	{
		if ((*str)[i] == '$')
		{
			i++;
			(*str) = ft_add_last_return(str, i, char_last_return);
		}
		else
			i++;
	}
	return (*str);
}
