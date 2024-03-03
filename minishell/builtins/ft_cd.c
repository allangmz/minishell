/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:51:12 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 17:05:02 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_change_pwd(char ***env)
{
	int		i;
	char	*buffer;

	buffer = NULL;
	i = ft_get_indice_variable((*env), "PWD");
	if (i == -1)
		return (-1);
	buffer = getcwd(buffer, 255);
	if (buffer == NULL)
		return (-1);
	free((*env)[i]);
	(*env)[i] = malloc(sizeof(char) * (ft_strlen(buffer) + 5));
	if (!((*env)[i]))
		return (-1);
	(*env)[i] = ft_strjoin("PWD=", buffer);
	if (!((*env)[i]))
		return (-1);
	return (0);
}

int	ft_change_oldpwd(char ***env, char *oldpwd)
{
	int		i;

	i = ft_get_indice_variable((*env), "OLDPWD");
	if (i == -1)
		return (0);
	free((*env)[i]);
	(*env)[i] = malloc(sizeof(char) * (ft_strlen(oldpwd) + 8));
	if (!((*env)[i]))
		return (-1);
	(*env)[i] = ft_strjoin("OLDPWD=", oldpwd);
	if (!((*env)[i]))
		return (-1);
	return (0);
}

void	cmen(char **cmd)
{
	DIR		*dir;

	cmd[1] += 2;
	dir = opendir(cmd[1]);
	if (dir)
	{
		chdir(getenv("HOME"));
		chdir(cmd[1]);
		closedir(dir);
	}
	else
	{
		fprintf(stderr, "cmd[1] %s\n", getenv("HOME"));
		fprintf(stderr, "cmd[1] %s\n", cmd[1]);
		cmd[1] -= 2;
		ft_putstr_fd("Minishell : cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
}

int	ft_cd(char **cmd, char ***env_copy)
{
	char	*buffer;

	if (cmd[1] && cmd[1][0] == '~')
		cmen(cmd);
	else
	{
		buffer = NULL;
		buffer = getcwd(buffer, 255);
		if (buffer == NULL)
			return (-1);
		if (ft_change_oldpwd(env_copy, buffer) != 0)
			return (-1);
		if (cmd[1] == NULL)
			chdir(getenv("HOME"));
		else if (cmd[1][0] == '-')
		{
			chdir(getenv("OLDPWD"));
			ft_pwd();
		}
		else if (chdir(cmd[1]) != 0)
			return (-1);
		ft_change_pwd(env_copy);
	}
	return (0);
}
