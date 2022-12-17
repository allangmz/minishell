/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_str_copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:21:49 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:23:02 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*make a copy of src. if n = 0 copy all the src*/
char	*ft_create_str_copy(char *src, int n)
{
	char	*copy;
	int		i;

	if (n == 0)
		n = ft_strlen(src);
	copy = malloc(sizeof(char) * (n + 1));
	i = 0;
	while (i < n)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
