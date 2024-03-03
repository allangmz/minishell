/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:54:23 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 19:57:44 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char **command_split, char *env[], char *variable)
{
	char	**path_list;
	char	*path;
	int		indice_path;

	indice_path = ft_get_indice_variable(env, variable);
	if (indice_path == -1)
	{
		return (NULL);
	}
	path_list = ft_split(env[indice_path] + 5, ':');
	path = ft_search_path(command_split, path_list);
	return (path);
}

char	*patate_name(char **command_split, char **env[])
{
	char	*pathname;

	if (!ft_strrchr(command_split[0], '/'))
	{
		pathname = ft_get_path(command_split, *env, "PATH");
		if (!pathname)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(command_split[0], 2);
			ft_putstr_fd(" : No such file or directory", 2);
			ft_putstr_fd("\n", 2);
			g_last_return = 127;
		}
	}
	else
	{
		pathname = ft_create_str_copy(command_split[0], 0);
	}
	return (pathname);
}

int	fourchette(char	**pathname, char **command_split, char **env[])
{
	int		pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: ft_exec_path: crash fork ", 2);
		ft_putstr_fd("\n", 2);
		free(pathname);
		g_last_return = 11;
		return (-3);
	}
	else if (pid == 0)
	{
		usleep(10);
		g_last_return = execve(*pathname, command_split, *env);
	}
	return (0);
}

int	let_me_in(char **pathname, char **command_split)
{
	if (*pathname == NULL || access(*pathname, X_OK) == -1)
	{
		ft_putstr_fd("Minishell: command not found: ", 2);
		ft_putstr_fd(command_split[0], 2);
		ft_putstr_fd("\n", 2);
		g_last_return = 127;
		free(pathname);
		return (-2);
	}
	return (0);
}

int	ft_exec_path(char **command_split, char **env[])
{
	char	*pathname;
	int		ret;

	if (!command_split)
	{
		ft_putstr_fd("commande vide\n", 2);
		return (-3);
	}
	pathname = patate_name(command_split, env);
	if (!pathname)
		return (-1);
	ret = let_me_in(&pathname, command_split);
	if (ret != 0)
		return (ret);
	ret = fourchette(&pathname, command_split, env);
	if (ret != 0)
		return (ret);
	wait(0);
	waitpid(-1, 0, 0);
	free(pathname);
	return (0);
}
