/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:23:55 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/07 11:27:27 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signo)
{
	if (signo == SIGINT)//ctrl-c
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0); // je sais pas comment le faire fonctionner faut demander a theo skuuuuuuuuuuuuuu
		rl_redisplay();
	}
	else if (signo == SIGQUIT)/* ctrl-\  */
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
}
