/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:57:32 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 19:04:40 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enter_redirect(char *entry, char *cmd)
{
	int		fdopen;
	char	**cmd_split;

	cmd_split = ft_split_minishell(cmd, ' ');
	fdopen = open(entry, O_RDONLY);
	close(STDIN_FILENO);
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
		if (ft_strcmp(line, delimiter) == 0)
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

// gerer les redirections multiples
// return string without repetition of redirection

void	exit_append_redirect(char *exit, char *cmd)
{
	int		fdopen;
	char	**cmd_split;

	cmd_split = ft_split_minishell(cmd, ' ');
	fdopen = open(exit, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fdopen, STDOUT_FILENO);
}
// cmd                        Stdin      envp   => fd
// cmd2                       fd    envp =>fd2
//  dup2()

//return l'index de la 1ere redirection
int	redirection_checker(char *str)
{
	int	i;

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

static void	ft_gestion_quote_count(char *str, int *i)
{
	if (str[*i] && str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\'')
		{
			*i += 1;
		}
		*i += 1;
	}
	if (str[*i] && str[*i] == '\"')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\"')
		{
			*i += 1;
		}
		*i += 1;
	}
}

t_redirection	ft_file2(t_redirection redirection, int i, char *str)
{
	int		j;
	int		limit[2];

	limit[0] = i;
	while (str[i] && !((str[i] >= '\t'
				&& str[i] <= '\r') || str[i] == ' '))
		i++;
	limit[1] = i;
	redirection.file = malloc(sizeof(char)
			* (limit[1] - limit[0] + 1));
	i = limit[0];
	j = 0;
	while (str[i] && !((str[i] >= '\t'
				&& str[i] <= '\r') || str[i] == ' '))
	{
		redirection.file[j] = str[i];
		i++;
		j++;
	}
	redirection.file[j] = '\0';
	return (redirection);
}

t_redirection	ft_file(char *str, int i)
{
	t_redirection	redirection;

	redirection.file = NULL;
	redirection.redirection = 0;
	while (str[i])
	{
		ft_gestion_quote_count(str, &i);
		if (str[i] == '>' || str[i] == '<')
		{
			redirection.redirection = ft_pick_redirection(str + i);
			i++;
			if (str[i] == '>' || str[i] == '<')
				i++;
			ft_gestion_quote_count(str, &i);
			while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
				i++;
			if (str[i] && !((str[i] >= '\t' && str[i] <= '\r')
					|| str[i] == ' '))
				return (ft_file2(redirection, i, str));
		}
		i++;
	}
	return (redirection);
}

int	red_loop(int *i, char **str)
{
	while ((*str)[*i] && !(((*str)[*i] >= '\t'
			&& (*str)[*i] <= '\r') || (*str)[*i] == ' '))
		(*i)++;
	return (*i);
}

void	red_if(char **str, int *i, int (*limit)[2])
{
	if ((*str)[*i] && !(((*str)[*i] >= '\t'
		&& (*str)[*i] <= '\r') || (*str)[*i] == ' '))
	{
		(*limit)[1] = red_loop(i, str);
		(*str) = ft_delete_nchar(str, (*limit)[0], (*limit)[1] - (*limit)[0]);
		return ;
	}
}

void	delete_redirection_to_str(char **str)
{
	int		limit[2];
	int		i;

	i = 0;
	while ((*str)[i])
	{
		ft_gestion_quote_count((*str), &i);
		if ((*str)[i] && ((*str)[i] == '>' || (*str)[i] == '<'))
		{
			limit[0] = i;
			i++;
			if ((*str)[i] && ((*str)[i] == '>' || (*str)[i] == '<'))
				i++;
			ft_gestion_quote_count((*str), &i);
			while ((*str)[i] && (((*str)[i] >= '\t'
					&& (*str)[i] <= '\r') || (*str)[i] == ' '))
				i++;
			limit[1] = i;
			red_if(str, &i, &limit);
		}
		i++;
	}
}

static void	exits(t_redirection redirection, char *str, int saved_std[2])
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

static void	opens(char *str, t_redirection	redirection, int saved_std[2])
{
	if (redirection.redirection == 4)
	{
		dup2(saved_std[0], STDIN_FILENO);
		here_doc(str, redirection.file);
	}
	else if (redirection.redirection == 3)
	{
		dup2(saved_std[0], STDIN_FILENO);
		enter_redirect(redirection.file, str);
	}
}

static int	loop_redirection(char **str, int saved_std[2], int *i)
{
	int				tmp;
	t_redirection	redirection;

	tmp = redirection_checker((*str) + (*i));
	if (tmp == -1)
		return (-1);
	(*i) = 0;
	redirection = ft_file((*str), (*i));
	delete_redirection_to_str(str);
	if (!redirection.file)
		return (-1);
	exits(redirection, (*str), saved_std);
	opens((*str), redirection, saved_std);
	if (redirection.file)
		free(redirection.file);
	return (0);
}

void	redirect_options(char *str, char ***envp)
{
	int		saved_std[2];
	char	**cmd_split;
	int		i;

	i = 0;
	saved_std[1] = dup(STDOUT_FILENO);
	saved_std[0] = dup(STDIN_FILENO);
	while (1)
	{
		if (loop_redirection(&str, saved_std, &i) == -1)
			break ;
	}
	cmd_split = ft_split_minishell(str, ' ');
	exec_command(cmd_split, envp);
	ft_free_doublechar(&cmd_split);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(saved_std[1], STDOUT_FILENO);
	dup2(saved_std[0], STDIN_FILENO);
}

char	*ft_cmd(char *str, int i)
{
	char	*cmd;
	char	**split;

	split = ft_split(str, str[i]);
	cmd = split[0];
	i = 1;
	ft_free_doublechar(&split);
	return (cmd);
}

int	redirections(char *cmd, char ***envp)
{
	int		i;
	char	**cmd_split;

	i = redirection_checker(cmd);
	if (ft_test(cmd, i) == -1)
	{
		return (-1);
	}
	if (i == -1)
	{
		cmd_split = ft_split_minishell(cmd, ' ');
		exec_command(cmd_split, envp);
		ft_free_doublechar(&cmd_split);
		return (0);
	}
	redirect_options(cmd, envp);
	return (0);
}
