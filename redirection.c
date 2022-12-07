/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:57:32 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/07 20:08:46 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <stdlib.h>
// #include <unistd.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <signal.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include </Users/tkempf-e/.brew/Cellar/readline/8.2.1/include/readline/readline.h>
// int	ft_strcmp(char *str1, char *str2)
// {
// 	int		i;

// 	if (!str1 && !str2)
// 		return (0);
// 	i = 0;
// 	while (str1[i] && str2[i] && str1[i] == str2[i])
// 		i++;
// 	if (!str1[i] && !str2[i])
// 		return (0);
// 	else
// 		return (-1);
// }

void	enter_redirect(char *entry, char *cmd, char **envp)
{
	int		fdopen;
	char	**cmd_split;
	int		pid;

	cmd_split = ft_split_minishell(cmd, ' ');
	fdopen = open(entry, O_RDONLY);
	dup2(fdopen, STDIN_FILENO);
	close(fdopen);
	pid = fork();
	if (pid == 0)
		exec_command(cmd_split, envp);
	ft_free_doublechar(&cmd_split);
	waitpid(pid, 0, 0);
}

/*
	cmd << delimiter
	faire que cat lise de lentree standard qui est dup avec str
*/
void	here_doc(char *cmd, char *delimiter, char **envp)
{
	char	*str;
	char	*line;
	int		fd;

	line = 0;
	str = 0;
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		str = ft_strjoin(str, ft_strjoin(line, "\n"));
	}
	fd = open(".hairdoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd(str, fd);
	free (str);
	close(fd);
	enter_redirect(".hairdoc", cmd, envp);
}

char	*ft_fdtostr(int fd)
{
	char	*str;
	char	buffer[2];
	int		octet;

	str = NULL;
	octet = read(fd, buffer, 1);
	buffer[1] = 0;
	str = ft_strjoin(str, buffer);
	while (octet > 0)
	{
		octet = read(fd, buffer, 1);
		buffer[octet] = 0;
		str = ft_strjoin(str, buffer);
	}
	return (str);
}

// cmd > exit
void	exit_redirect(char *exit, char *cmd, char **envp)
{
	int		fdopen;
	int		fd[2];
	char	**cmd_split;
	char	*path;
	int		pid;

	cmd_split = ft_split_minishell(cmd, ' ');
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_command(cmd_split, envp);
	}
	close(fd[1]);
	path = ft_fdtostr(fd[0]);
	close(fd[0]);
	fdopen = open(exit, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd(path, fdopen);
	ft_free_doublechar(&cmd_split);
	close(fdopen);
	waitpid(pid, 0, 0);
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

char	*filer_the_creator(char *str, int redirect_nbr)
{
	(void) redirect_nbr; // pourquoi cette varible existe ?
	int		i;
	char	**no_redirect;
	char	*file;

	no_redirect = ft_split(str, '>');
	i = 0;
	while (no_redirect[i])// enlever les ' ' et '>' en trop
	{
		file = ft_strtrim(no_redirect[i], " ><");
		free (no_redirect[i]);
		no_redirect[i] = file;
		i++;
	}
	i = 1;
	while (no_redirect[i] && no_redirect[i + 1])
	{
		open(no_redirect[i], O_CREAT | O_RDWR , 0644);
		i++;
	}
	return (ft_strjoin(no_redirect[0], ft_strjoin(" > ", no_redirect[i])));
}

// gerer les redirections multiples
// return string without repetition of redirection
char	*pre_redirect(char *str)
{
	char	*new_str;
	int		redirect_nbr;
	
	redirect_nbr = redirection_counter(str);
	if (redirect_nbr < 2)
		return (str);
	new_str = filer_the_creator(str, redirect_nbr);
	return (new_str);
}

void	exit_append_redirect(char *exit, char *cmd, char **envp)
{
	int		fdopen;
	int		fd[2];
	char	**cmd_split;
	char	*path;
	int		pid;

	cmd_split = ft_split_minishell(cmd, ' ');
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_command(cmd_split, envp);
	}
	close(fd[1]);
	path = ft_fdtostr(fd[0]);
	close(fd[0]);
	fdopen = open(exit, O_CREAT | O_RDWR | O_APPEND, 0644);
	ft_putstr_fd(path, fdopen);
	ft_free_doublechar(&cmd_split);
	close(fdopen);
	waitpid(pid, 0, 0);
}
// cmd                        Stdin      envp   => fd
// cmd2                       fd    envp =>fd2
//  dup2()

//return l'index de la 1ere redirection
int	redirection_checker(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (i > 0 && (str[i] == '<' || str[i] == '>')
			&& (str[i] == str[i - 1] || str[i - 1] == ' '))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isalnum(int c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97)
		|| (c >= 48 && c <= 57) || c == ' ')
		return (0);
	return (-1);
}

int	ft_test(char *str, int i)
{
	if (i > 0 && (str[i + 1] != str[i] && ft_isalnum(str[i + 1]) == -1))
	{
		printf("Minishell: syntax error near unexpected token '%c'\n", str[i]);
		return (-1);
	}
	return (0);
}

void	redirect_options(char *str, char *cmd, char *file, char **envp)
{
	int		i;

	i = redirection_checker(str);
	if (str[i] == '>' && str[i + 1] == '>')
		exit_append_redirect(file, cmd, envp);
	else if (str[i] == '>')
		exit_redirect(file, cmd, envp);
	else if (str[i] == '<' && str[i + 1] == '<')
		here_doc(cmd, file, envp);
	else if (str[i] == '<')
		enter_redirect(file, cmd, envp);
}

char	*ft_cmd(char *str, int i, int *ptrj)
{
	(void) ptrj; //pourquoi il existe ?
	char	*cmd;
	char	**split;

	split = ft_split(str, str[i]);
	cmd = split[0];
	i = 1;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free (split);
	return (cmd);
}

char	*ft_file(char *str, int i, int *ptrj)
{
	(void) ptrj; //pourquoi il existe ?
	char	*file;
	char	**split;

	split = ft_split(str, str[i]);
	file = ft_strtrim(split[1], " ");
	i = 0;
	while (split[i] && split[i + 1])
	{
		free(split[i]);
		i++;
	}
	free (split);
	return (file);
}

int	redirections(char *cmd, char **envp)
{
	int		i;
	int		j;
	char	*file;
	char	*new_str;
	char 	**cmd_split;

	i = redirection_checker(cmd);
	if (ft_test(cmd, i) == -1)
		return (-1);
	if (i == -1)
	{
		cmd_split = ft_split_minishell(cmd, ' ');
		exec_command(cmd_split, envp);
		return (0);
	}
	new_str = pre_redirect(cmd);
	cmd = ft_cmd(new_str, i, &j);
	file = ft_file(new_str, i, &j);
	redirect_options(new_str, cmd, file, envp);
	free(file);
	return (0);
}