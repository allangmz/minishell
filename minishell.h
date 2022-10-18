/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:59:13 by aguemazi          #+#    #+#             */
/*   Updated: 2022/10/07 10:43:41 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>

int		ft_get_indice_variable(char *env[], char *variable);
char	*test(char *str, char *env[], int last_return);
int		ft_exec_path(char **command_split, char *env[]);
void	ft_free_doublechar(char ***tab);
char	**ft_split_minishell(char *s, char sep);
char	*ft_add_str_in_str(char *s1, char *s2, int begin);
char	*ft_delete_nchar(char *str, int begin, int n);
char	*ft_expand_string_variables(char *str, char *env[], size_t begin,
			size_t n);
char	*get_variable_in_env(char *env[], char *variable);
char	*ft_expand_last_return(char *str, char *char_last_return, size_t begin,
			size_t n);

#endif