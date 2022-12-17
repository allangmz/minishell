/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:55:11 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 18:52:09 by aguemazi         ###   ########.fr       */
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

int	exec_command(char **cmd, char ***env_copy)
{
	if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		g_last_return = ft_cd(cmd, env_copy);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_print_env(env_copy);
	else if (ft_strcmp(cmd[0], "export") == 0)
		g_last_return = ft_export_variable_env(env_copy, cmd[1]);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset_variable_env(env_copy, cmd[1]);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(g_last_return);
	}
	else
	{
		usleep(10);
		g_last_return = ft_exec_path(cmd, env_copy);
	}
	return (0);
}

int	ft_pipe(char *cmd, int inputfd, char ***env_copy)
{
	int		fd[2];

	pipe(fd);
	dup2(inputfd, STDIN_FILENO);
	close(inputfd);
	dup2(fd[1], STDOUT_FILENO);
	if (redirections(cmd, env_copy) == -1)
		return (-4);
	close(fd[1]);
	return (fd[0]);
}

int	ft_pipe_last(char *cmd, int inputfd, char ***env_copy)
{
	usleep(10);
	close(STDIN_FILENO);
	dup2(inputfd, STDIN_FILENO);
	usleep(2);
	redirections(cmd, env_copy);
	close(inputfd);
	return (0);
}

void	lire_pipe(int pipe_fd)
{
	char	buffer[1024];
	int		ret;

	ret = read(pipe_fd, buffer, 1023);
	while (ret != 0)
	{
		buffer[ret] = 0;
		ret = read(pipe_fd, buffer, 1023);
	}
}

int	ft_isforbiden(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '(' || c == ')')
		return (-1);
	return (0);
}

int	check_str2(char *str)
{
	int		i;	

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (ft_isalnum(str[i]) == -1)
			{
				if (str[i] == '|')
				{
					printf("Minishell : Parse error near \'|\'\n");
					return (-1);
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	check_str3(char *str)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	if (str[i])
	{
		while (str[i] && ft_isforbiden(str[i]) == -1)
			i++;
		while (str[i])
		{
			if (ft_isforbiden(str[i]) == 0)
				check = 1;
			i++;
		}
		if (check == 0)
			return (-1);
	}
	return (0);
}

int	check_str(char *str)
{
	int		i;

	i = 0;
	if (!str[i])
	{
		return (-1);
	}
	if (check_str2(str) == -1)
		return (-1);
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (-1);
	if (ft_isalnum(str[i]) == -1 && str[i] != '/'
		&& str[i] != '\'' && str[i] != '\"' && str[i] != '.')
	{
		printf("Minishell : syntax error near unexpected token \'%c\'\n", str[i]);
		return (-1);
	}
	if (check_str3(str) == -1)
		return (-1);
	return (0);
}

int	check_empty(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}

void	your_name(char **tab_pipe, int fd, int saved_std[2], char ***env_copy)
{
	int		i;

	i = 0;
	while (tab_pipe && tab_pipe[i])
	{
		usleep(10);
		if (tab_pipe[i + 1])
		{
			dup2(saved_std[1], STDOUT_FILENO);
			fd = ft_pipe(tab_pipe[i], fd, env_copy);
			dup2(saved_std[0], STDIN_FILENO);
		}
		else
		{
			dup2(saved_std[1], STDOUT_FILENO);
			ft_pipe_last(tab_pipe[i], fd, env_copy);
			close(fd);
		}
		i++;
	}
}

void	no_name(char *str, char ***env_copy, int saved_std[2])
{
	int		i;
	int		fd;
	char	**tab_pipe;

	i = 0;
	tab_pipe = ft_split_pipe(str);
	fd = STDIN_FILENO;
	your_name(tab_pipe, fd, saved_std, env_copy);
	close (fd);
	if (tab_pipe)
		ft_free_doublechar(&tab_pipe);
}

int	ft_minishell(int saved_std[2], char ***env_copy)
{
	char	*str;

	while (1)
	{
		dup2(saved_std[1], STDOUT_FILENO);
		dup2(saved_std[0], STDIN_FILENO);
		str = readline("Minishell : ");
		if (!str)
			return (0);
		if (check_empty(str) == -1)
			continue ;
		usleep(20);
		add_history(str);
		str = translate_variable(str, *env_copy);
		if (check_str(str) == -1)
			continue ;
		no_name(str, env_copy, saved_std);
		free(str);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	**env_copy;
	int		last_return;
	int		saved_std[2];

	(void) argc;
	(void) argv;
	env_copy = ft_copy_env(env);
	saved_std[1] = dup(1);
	saved_std[0] = dup(0);
	last_return = 0;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	return (ft_minishell(saved_std, &env_copy));
}
