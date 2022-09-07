/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:55:11 by aguemazi          #+#    #+#             */
/*   Updated: 2022/09/05 13:13:02 by aguemazi         ###   ########.fr       */
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
#include <signal.h>

void changement_signal(int signal)
{
	if (signal == 2)
		fprintf(stdin,"\b\nMinishell : ");
	if (signal == 3)
		printf("\b");
		// printf("signal %d\n",signal);
}
int	main(int argc, char **argv, char **env)
{
	int		last_return;
	char	*str;
	char	**str_split;

	(void) argc;
	(void) argv;
	struct sigaction test_signal;
	test_signal.sa_handler = changement_signal;
	last_return = 0;
	sigaction(SIGQUIT, &test_signal, NULL);
	sigaction(SIGINT, &test_signal, NULL);
	while (1)
	{
		str = readline("\nMinishell : ");
		add_history(str);
		if (str)
		{
			str = test(str, env, last_return);
			str_split = ft_split_minishell(str);

			printf("test %s\n",str_split[1]);
			last_return = ft_exec_path(str_split, env);
			ft_free_doublechar(&str_split);
			free(str);
		}
	}
	return (0);
}