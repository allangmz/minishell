/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:55:11 by aguemazi          #+#    #+#             */
/*   Updated: 2022/08/18 17:59:56 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../Libft/libft.h"
#include <sys/types.h>
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	while (1)
	{
		char *str;
		char **str_split;
		str = readline("Minishel : ");
		add_history(str);
		if (str)
		{
			str = test(str, env);
			str_split = ft_split_minishell(str);
			ft_exec_path(str_split, env);
			
			ft_free_doublechar(&str_split);
			free(str);
		}
	}
	return (0);
}