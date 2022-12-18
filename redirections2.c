/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:25:39 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/18 19:59:10 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cmd << delimiter
	faire que cat lise de lentree standard qui est dup avec str
*/
void	here_doc(char *cmd, char *delimiter)
{
	char	*str;
	char	*line;
	int		saved_std;
	int		fd;

	line = 0;
	str = 0;
	saved_std = dup(STDOUT_FILENO);
	fd = open(".hairdoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		dup2(1, STDOUT_FILENO);
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		dup2(fd, STDOUT_FILENO);
		ft_putstr_fd(line, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		dup2(saved_std, STDOUT_FILENO);
	}
	close(fd);
	enter_redirect(".hairdoc", cmd);
}

// cmd > exit
void	exit_redirect(char *exit)
{
	int		fdopen;

	fdopen = open(exit, O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fdopen, STDOUT_FILENO);
}

void	enter_redirect(char *entry, char *cmd)
{
	int		fdopen;
	char	**cmd_split;

	cmd_split = ft_split_minishell(cmd, ' ');
	fdopen = open(entry, O_RDONLY);
	close(STDIN_FILENO);
	dup2(fdopen, STDIN_FILENO);
}

int	redirection_counter(char *str)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			counter++;
			if (str[i + 1] && str[i + 1] == str[i])
				i++;
		}
		i++;
	}
	return (counter);
}

void	exit_append_redirect(char *exit, char *cmd)
{
	int		fdopen;
	char	**cmd_split;

	cmd_split = ft_split_minishell(cmd, ' ');
	fdopen = open(exit, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fdopen, STDOUT_FILENO);
}
