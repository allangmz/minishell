/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:57:32 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:39:29 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
