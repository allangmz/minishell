/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translate_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:05:22 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:05:41 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
