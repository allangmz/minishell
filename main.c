/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:55:11 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/07 11:43:17 by aguemazi         ###   ########.fr       */
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

// make a copy of src. if n = 0 copy all the src
// char	*ft_create_str_copy(char *src, int n)
// {
// 	char	*copy;
// 	int		i;

// 	if (n == 0)
// 		n = ft_strlen(src);
// 	copy = malloc(sizeof(char) * (n + 1));
// 	i = 0;
// 	while (i < n)
// 	{
// 		copy[i] = src[i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }


int exec_command(char **cmd, char **env_copy)
{
	int		last_return;


	last_return = 0;
	if (ft_strcmp(cmd[0], "pwd") == 0) // qund PWD est unset ca detruis OLDPWD ?
		ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd, &env_copy);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_print_env(env_copy);// valeur de retour last_return
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export_variable_env(&env_copy, cmd[1]); // verifier que la valeur est presente
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset_variable_env(&env_copy, cmd[1]);// valeur de retour last_return
	else if (ft_strcmp(cmd[0], "echo") == 0)	
		ft_echo(cmd); // valeur de retour last_return
	else
		last_return = ft_exec_path(cmd, env_copy); // gerer le last return
	return (last_return);
}

int	ft_pipe(char **cmd, int inputfd, char **env_copy)
{
	int		fd[2];
	char	*buffer;

	pipe(fd);
	buffer = NULL;
	// close(fd[0]);
	if (dup2(inputfd, STDIN_FILENO) == -1)
		fprintf(stderr,"GROSSE MERDE 1 ");
	close(inputfd);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		fprintf(stderr,"GROSSE MERDE 2");
	if (exec_command(cmd, env_copy) != 0)
	{
		fprintf(stderr,"GROSSE MERDE 3");
		return (-1);
	}
	close(fd[1]);
	return (fd[0]);
}

int	ft_pipe_last(char **cmd, int inputfd, char **env_copy)
{
	int		fd[2];
	char	*buffer;


	buffer = NULL;
	close(fd[1]);
	close(fd[0]);
	dup2(inputfd, STDIN_FILENO);
	exec_command(cmd, env_copy);
	return (0);
}

void lire_pipe(int pipe_fd)
{
	char      buffer[1024];
      int       ret;

      while ((ret = read(pipe_fd, buffer, 1023)) != 0)
      {
        fprintf(stderr,"%d\n", ret);
        buffer[ret] = 0;
        fprintf(stderr,"%s\n", buffer);
      }
}


int	main(int argc, char **argv, char **env)
{
	char	**env_copy;
	int		last_return;
	char	*str;
	char	**str_split;
	char	**tab_pipe;
	char	*buffer;
	int		fd;	
	int		i;
	int		saved_stdout;
	int		saved_stdin;

	(void) argc;
	(void) argv;
	env_copy = ft_copy_env(env);
	saved_stdout = dup(1);
	saved_stdin = dup(0);
	last_return = 0;
	buffer = NULL;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	while (1)
	{
		// fprintf(stderr,"test\n");
		str = readline("Minishell : ");
		if (!str)
		{
			return (0);
		}
		// fprintf(stderr,"test\n");
		usleep(20);
		add_history(str);
		i = 0;
		tab_pipe = ft_split_pipe(str);
		fd = STDIN_FILENO;
		free(str);
		while (tab_pipe && tab_pipe[i])
		{
			tab_pipe[i] = test(tab_pipe[i], env_copy, last_return); // renomme les variable selon "" ''
			str_split = ft_split_minishell(tab_pipe[i], ' '); // split les espace selon les "" ''
			if (tab_pipe[i + 1])
			{
				dup2(saved_stdout, STDOUT_FILENO);
				fd = ft_pipe(str_split, fd, env_copy);
				dup2(saved_stdin, STDIN_FILENO);
			}	
			else
			{
				// lire_pipe(fd);
				dup2(saved_stdout, STDOUT_FILENO);
				ft_pipe_last(str_split, fd, env_copy);
			}
			i++;
		}
		close (fd);
		if (tab_pipe)
			ft_free_doublechar(&tab_pipe);
		dup2(saved_stdin, STDIN_FILENO);
		// fprintf(stderr,"i   %d", i);
	}
	return (0);
}

// rajouter des protection sur toute les fonctions + les retour pour $? de chaque fonction + verifier que tout soit free au bon moment

// errreur ----> echo "cat | cat | cat | cat |" | cat