/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:31:58 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 21:50:48 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exits(t_redirection redirection, char *str, int saved_std[2])
{
	if (redirection.redirection == 2)
	{
		dup2(saved_std[1], STDOUT_FILENO);
		exit_append_redirect(redirection.file, str);
	}
	else if (redirection.redirection == 1)
	{
		dup2(saved_std[1], STDOUT_FILENO);
		exit_redirect(redirection.file);
	}
}
