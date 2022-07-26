/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_string_variables.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:30:07 by aguemazi          #+#    #+#             */
/*   Updated: 2022/07/26 16:29:16 by aguemazi         ###   ########.fr       */
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

char	*ft_add_variable(char *str, int i, int j, char *env[])
{
	char	*variable;

	variable = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(variable, str + i - j, j + 1);
	variable = get_variable_in_env(env, variable);
	str = ft_delete_nchar(str, i - (j + 1), j + 1);
	if (variable)
		str = ft_add_str_in_str(str, variable, i - j - 1);
	return (str);
}

char	*ft_expand_string_variables(char *str, char *env[])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			j = 0;
			while (str[i] && ft_isalnum(str[i]))
			{
				i++;
				j++;
			}
			str = ft_add_variable(str, i, j, env);
		}
		else
			i++;
	}
	return (str);
}

// int main(int argc, char **argv, char *env[])
// {
// 	(void) argc;
// 	(void) argv;
// 	char *test =  "sddsdf $HOME$PATH fs";
// 	printf ("\n\nresultat %s\n",ft_expand_string_variables(test,env));
// }
