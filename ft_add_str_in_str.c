/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:24:08 by aguemazi          #+#    #+#             */
/*   Updated: 2022/08/25 14:11:37 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_str_in_str(char *s1, char *s2, int begin)
{
	size_t	newsize;
	char	*newstr;
	int		i;
	int		j;

	newsize = ft_strlen(s1) + ft_strlen(s2);
	newstr = malloc(sizeof(char) * newsize + 1);
	if (!newstr)
	{
		printf("ft_delete_nchar: malloc crash\n");
		return (NULL);
	}
	i = 0;
	while (i < begin)
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	while (s1[i - j])
	{
		newstr[i] = s1[i - j];
		i++;
	}
	newstr[i] = '\0';
	free (s1);
	// free (s2);
	return (newstr);
}