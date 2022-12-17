/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:29:59 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:30:57 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	ft_file2(t_redirection redirection, int i, char *str)
{
	int		j;
	int		limit[2];

	limit[0] = i;
	while (str[i] && !((str[i] >= '\t'
				&& str[i] <= '\r') || str[i] == ' '))
		i++;
	limit[1] = i;
	redirection.file = malloc(sizeof(char)
			* (limit[1] - limit[0] + 1));
	i = limit[0];
	j = 0;
	while (str[i] && !((str[i] >= '\t'
				&& str[i] <= '\r') || str[i] == ' '))
	{
		redirection.file[j] = str[i];
		i++;
		j++;
	}
	redirection.file[j] = '\0';
	return (redirection);
}

t_redirection	ft_file(char *str, int i)
{
	t_redirection	redirection;

	redirection.file = NULL;
	redirection.redirection = 0;
	while (str[i])
	{
		ft_gestion_quote_count(str, &i);
		if (str[i] == '>' || str[i] == '<')
		{
			redirection.redirection = ft_pick_redirection(str + i);
			i++;
			if (str[i] == '>' || str[i] == '<')
				i++;
			ft_gestion_quote_count(str, &i);
			while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
				i++;
			if (str[i] && !((str[i] >= '\t' && str[i] <= '\r')
					|| str[i] == ' '))
				return (ft_file2(redirection, i, str));
		}
		i++;
	}
	return (redirection);
}

int	red_loop(int *i, char **str)
{
	while ((*str)[*i] && !(((*str)[*i] >= '\t'
			&& (*str)[*i] <= '\r') || (*str)[*i] == ' '))
		(*i)++;
	return (*i);
}

void	red_if(char **str, int *i, int (*limit)[2])
{
	if ((*str)[*i] && !(((*str)[*i] >= '\t'
		&& (*str)[*i] <= '\r') || (*str)[*i] == ' '))
	{
		(*limit)[1] = red_loop(i, str);
		(*str) = ft_delete_nchar(str, (*limit)[0], (*limit)[1] - (*limit)[0]);
		return ;
	}
}

void	delete_redirection_to_str(char **str)
{
	int		limit[2];
	int		i;

	i = 0;
	while ((*str)[i])
	{
		ft_gestion_quote_count((*str), &i);
		if ((*str)[i] && ((*str)[i] == '>' || (*str)[i] == '<'))
		{
			limit[0] = i;
			i++;
			if ((*str)[i] && ((*str)[i] == '>' || (*str)[i] == '<'))
				i++;
			ft_gestion_quote_count((*str), &i);
			while ((*str)[i] && (((*str)[i] >= '\t'
					&& (*str)[i] <= '\r') || (*str)[i] == ' '))
				i++;
			limit[1] = i;
			red_if(str, &i, &limit);
		}
		i++;
	}
}
