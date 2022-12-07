/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:56:59 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/07 11:32:34 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(buffer, 255); //last_return ?
	printf("%s\n", buffer);
}
