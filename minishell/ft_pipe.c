/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:17:09 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:23:08 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
