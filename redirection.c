/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:57:32 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/13 17:13:02 by tkempf-e         ###   ########.fr       */
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



char	*ft_strjoin_test(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	j = 0;
	i = 0;
	sleep(1);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1 && s1[i])
	{
		join[i] = *(char *)(s1 + i);
		i++;
	}
	while (s2[j])
	{
		join[i + j] = *(char *)(s2 + j);
		j++;
	}
	join[i + j] = '\0';
	free(s1); // faut surement free
	return (join);
}

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

void	enter_redirect(char *entry, char *cmd)
{
	int		fdopen;
	char	**cmd_split;

	cmd_split = ft_split_minishell(cmd, ' ');
	fdopen = open(entry, O_RDONLY);
	dup2(fdopen, STDIN_FILENO);
}

/*
	cmd << delimiter
	faire que cat lise de lentree standard qui est dup avec str
*/
void	here_doc(char *cmd, char *delimiter)
{
	char	*str;
	char	*line;
	int		saved_stdout;
	int		fd;

	line = 0;
	str = 0;
	saved_stdout = dup(STDOUT_FILENO);
	fd = open(".hairdoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		dup2(1, STDOUT_FILENO);
		line = readline("heredoc> ");
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		dup2(fd, STDOUT_FILENO);
		ft_putstr_fd(line, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
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

void	exit_append_redirect(char *exit, char *cmd)
{
	int		fdopen;
	int		saved_stdout;
	char	**cmd_split;

	cmd_split = ft_split_minishell(cmd, ' ');
	saved_stdout = dup(STDOUT_FILENO);
	fdopen = open(exit, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fdopen, STDOUT_FILENO);
}
// cmd                        Stdin      envp   => fd
// cmd2                       fd    envp =>fd2
//  dup2()

//return l'index de la 1ere redirection
int	redirection_checker(char *str)
{
	int i;
	
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
		if (i > 0 && (str[i] == '<' || str[i] == '>'))
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
		printf("Minishell : syntax error near unexpected token '%c'\n", str[i]);
		return (-1);
	}
	return (0);
}

int	ft_pick_redirection(char *str)
{
	int	i;
	int	redirection;

	i = 0;
	if (str[i] == '>')
	{
		redirection = 1;
		i++;
		if (str[i] == '>')
		{
			redirection = 2;
		}
	}
	if (str[i] == '<')
	{
		redirection = 3;
		i++;
		if (str[i] == '<')
		{
			redirection = 4;
		}
	}
	return (redirection);
}

t_redirection	ft_file(char *str, int i)
{
	int				limit[2];
	int				j;
	t_redirection	redirection;

	redirection.file = NULL;
	redirection.redirection = 0;
	while (str[i])
	{
		// ajouter gestion quote
		if (str[i] == '>' || str[i] == '<')
		{
			redirection.redirection = ft_pick_redirection(str + i);
			i++;
			if (str[i] == '>' || str[i] == '<')
			{
				i++;
			}
			// ajouter gestion quote
			while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
			{
				i++;
			}
			if (str[i] && !((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
			{
				limit[0] = i;
				// fprintf(stderr, "TEST limit[0] %c\n", str[i]);
				while (str[i] && !((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
				{
					i++;
				}
				limit[1] = i;
				// fprintf(stderr, "TEST limit[1] %c\n", str[i]);
				redirection.file = malloc(sizeof(char) * (limit[1] - limit[0]));
				i = limit[0];
				j = 0;
				while (str[i] && !((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
				{
					redirection.file[j] = str[i];
					i++;
					j++;
				}
				return (redirection);
			}
		}
		i++;
	}
	return (redirection);
}

void	delete_redirection_to_str(char **str)
{
	int		limit[2];
	int		i;

	i = 0;
	while ((*str)[i])
	{
		// ajouter gestion quote
		if ((*str)[i] == '>' || (*str)[i] == '<')
		{
			limit[0] = i;
			i++;
			if ((*str)[i] == '>' || (*str)[i] == '<')
			{
				i++;
			}
			// ajouter gestion quote
			while (((*str)[i] >= '\t' && (*str)[i] <= '\r') || (*str)[i] == ' ')
			{
				i++;
			}
			limit[1] = i;
			if ((*str)[i] && !(((*str)[i] >= '\t' && (*str)[i] <= '\r') || (*str)[i] == ' '))
			{
				while ((*str)[i] && !(((*str)[i] >= '\t' && (*str)[i] <= '\r') || (*str)[i] == ' '))
				{
					i++;
				}
				limit[1] = i;
				(*str) = ft_delete_nchar((*str), limit[0], limit[1] - limit[0]); //je sai pas si ca marche
				return ;
			}
		}
		i++;
	}
	return ;
}

void	redirect_options(char *str, char **envp)
{
	int				i;
	int				saved_stdout;
	int				saved_stdin;
	char			**cmd_split;
	t_redirection	redirection;
	int				tmp;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	i = 0;
	while (str[i]) // cat  > text2 > test3 > test4 < text1
	{
		// dup2(saved_stdout, STDOUT_FILENO);
		// dup2(saved_stdin, STDIN_FILENO);
		tmp = redirection_checker(str + i);
		if (tmp == -1)
			break ;
		i = 0;
		redirection = ft_file(str, i);
		delete_redirection_to_str(&str);
		if (!redirection.file)
			break ;	
	 	// fprintf(stderr, "TEST file %s\n", redirection.file);
		// fprintf(stderr, "TEST redirec %d\n", redirection.redirection);
		// fprintf(stderr, "TEST str %s %d\n", str, i);
		if (redirection.redirection == 2)
		{
			dup2(saved_stdout, STDOUT_FILENO);
			exit_append_redirect(redirection.file, str);
		}
		else if (redirection.redirection == 1)
		{
			dup2(saved_stdout, STDOUT_FILENO);
			exit_redirect(redirection.file);
		}
		else if (redirection.redirection == 4)
		{
			dup2(saved_stdin, STDIN_FILENO);
			here_doc(str, redirection.file);
		}
		else if (redirection.redirection == 3)
		{
			dup2(saved_stdin, STDIN_FILENO);
			enter_redirect(redirection.file, str);
		}
		if (redirection.file)
			free(redirection.file);
	}
	cmd_split = ft_split_minishell(str, ' ');
	exec_command(cmd_split, envp);
	ft_free_doublechar(&cmd_split);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDIN_FILENO);
}

char	*ft_cmd(char *str, int i, int *ptrj)
{
	(void) ptrj; //pourquoi il existe ?
	char	*cmd;
	char	**split;

	split = ft_split(str, str[i]);
	cmd = split[0];
	i = 1;
	ft_free_doublechar(&split);
	return (cmd);
}

int	redirections(char *cmd, char **envp)
{
	int		i;
	char 	**cmd_split;

	i = redirection_checker(cmd);
	if (ft_test(cmd, i) == -1)
		return (-1);
	if (i == -1)
	{
		cmd_split = ft_split_minishell(cmd, ' ');
		exec_command(cmd_split, envp);
		ft_free_doublechar(&cmd_split);
		return (0);
	}
	// new_str = pre_redirect(cmd);
	// cmd = ft_cmd(new_str, i, &j);
	// file = ft_file(new_str, i, &j);
	redirect_options(cmd,envp);
	return (0);
}