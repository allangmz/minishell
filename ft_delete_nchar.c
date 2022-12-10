/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_nchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:47:15 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/10 11:49:46 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_until_the_end(int newsize, char *newstr, char *str)
{
	int	i;

	i = 0;
	newstr = malloc(sizeof(char) * newsize + 1);
	if (!newstr)
	{
		printf("ft_delete_nchar: malloc crash\n");
		free(str);
		return (NULL);
	}
	while (i < newsize)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*delete_not_until_the_end(int newsize, char *newstr, char *str
	, int limit[])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	newstr = malloc(sizeof(char) * newsize + 1);
	if (!newstr)
	{
		printf("ft_delete_nchar: malloc crash\n");
		free(newstr);
		return (NULL);
	}
	while (i < limit[0])
	{
		newstr[i] = str[i];
		i++;
	}
	j = 0;
	while (str[limit[1] + j] != '\0')
	{
		newstr[i] = str[limit[1] + j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}		

/* 
	begin = index of the word to be deleted
	n = number of char to delete
*/
char	*ft_delete_nchar(char *str, int begin, int n)
{
	int		size;
	char	*newstr;
	int		limit[2];

	limit[0] = begin;
	limit[1] = begin + n;
	newstr = NULL;
	if (begin < 0 || n < 0)
	{
		printf("ft_delete_nchar: begin or n incorrect\n");
		return (NULL);
	}
	size = ft_strlen(str);
	if (size < limit[1])
	{
		newstr = delete_until_the_end(size - (size - begin), newstr, str);
	}
	else
	{
		newstr = delete_not_until_the_end(size - n, newstr, str, limit);
	}
	free(str);
	return (newstr);
}
