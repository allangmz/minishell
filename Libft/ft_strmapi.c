/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:52:12 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/04 14:27:03 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s2;
	size_t	i;

	if (!s)
		return (0);
	s2 = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s2)
		return (0);
	i = 0;
	while (s[i])
	{
		s2[i] = f(i, (char ) s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
