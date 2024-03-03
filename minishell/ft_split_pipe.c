/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:39:33 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 21:49:07 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_gestion_quote_count2(char *str, int *i, int *command_count)
{
	if (str[*i] && str[*i] == '\'')
	{
		*i += 1;
		*command_count += 1;
		while (str[*i] && str[*i] != '\'')
		{
			*i += 1;
			*command_count += 1;
		}
		*i += 1;
		*command_count += 1;
	}
	if (str[*i] && str[*i] == '\"')
	{
		*i += 1;
		*command_count += 1;
		while (str[*i] && str[*i] != '\"')
		{
			*i += 1;
			*command_count += 1;
		}
		*i += 1;
		*command_count += 1;
	}
}

void	ft_malloc_command(char ***tab_pipe, char *str)
{
	int	i;
	int	j;
	int	command_count;

	command_count = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		ft_gestion_quote_count2(str, &i, &command_count);
		if (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '|')
		{
			i++;
			command_count++;
		}
		if (str[i] && str[i] == '|')
		{
			(*tab_pipe)[j] = malloc(sizeof(char *) * command_count + 1);
			(*tab_pipe)[j++][command_count] = '\0';
			i++;
			command_count = 0;
		}
	}
	(*tab_pipe)[j] = malloc(sizeof(char *) * command_count + 1);
	(*tab_pipe)[j][command_count] = '\0';
}

void	ft_copy_gestion_pipe(char *str, char ***tab_pipe,
							int *command_count, int (*i)[2], char quote)
{
	if (str[(*i)[0]] && str[(*i)[0]] == quote)
	{
		(*tab_pipe)[(*i)[1]][*command_count] = str[(*i)[0]];
		*command_count += 1;
		(*i)[0] += 1;
		while (str[(*i)[0]] && str[*i[0]] != quote)
		{
			(*tab_pipe)[(*i)[1]][*command_count] = str[(*i)[0]];
			(*i)[0] += 1;
			*command_count += 1;
		}
		(*tab_pipe)[(*i)[1]][*command_count] = str[(*i)[0]];
		(*i)[0] += 1;
		*command_count += 1;
	}
}

void	ft_copy_command(char ***tab_pipe, char *str)
{
	int		indice[2];
	int		command_count;

	indice[0] = 0;
	indice[1] = 0;
	command_count = 0;
	while (str[indice[0]])
	{
		ft_copy_gestion_pipe(str, tab_pipe, &command_count, &indice, '\'');
		ft_copy_gestion_pipe(str, tab_pipe, &command_count, &indice, '\"');
		if (str[indice[0]] && str[indice[0]] != '\''
			&& str[indice[0]] != '\"' && str[indice[0]] != '|')
		{
			(*tab_pipe)[indice[1]][command_count] = str[indice[0]];
			indice[0]++;
			command_count++;
		}
		if (str[indice[0]] && str[indice[0]] == '|')
		{
			indice[0]++;
			indice[1]++;
			command_count = 0;
		}
	}
}

char	**ft_split_pipe(char *str)
{
	char	**tab_pipe;
	int		pipe_count;

	if (!str)
		return (NULL);
	pipe_count = ft_count_pipe(str);
	tab_pipe = malloc(sizeof(char *) * pipe_count + 1);
	tab_pipe[pipe_count] = NULL;
	ft_malloc_command(&tab_pipe, str);
	ft_copy_command(&tab_pipe, str);
	return (tab_pipe);
}
