/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:24:08 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 21:03:16 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_copie(char *s2, char **s1, int *i, char **newstr)
{
	int	j;

	j = 0;
	while (s2[j])
	{
		(*newstr)[*i] = s2[j];
		*i += 1;
		j++;
	}
	while ((*s1)[(*i) - j])
	{
		(*newstr)[*i] = (*s1)[(*i) - j];
		*i += 1;
	}
	(*newstr)[*i] = '\0';
}

char	*ft_add_str_in_str(char **s1, char *s2, int begin)
{
	size_t	newsize;
	char	*newstr;
	int		i;

	newsize = ft_strlen(*s1) + ft_strlen(s2);
	newstr = malloc(sizeof(char) * newsize + 1);
	if (!newstr)
	{
		printf("ft_delete_nchar: malloc crash\n");
		return (NULL);
	}
	i = 0;
	while (i < begin)
	{
		newstr[i] = (*s1)[i];
		i++;
	}
	ft_copie(s2, s1, &i, &newstr);
	free (*s1);
	return (newstr);
}
