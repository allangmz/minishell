/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:59:13 by aguemazi          #+#    #+#             */
/*   Updated: 2022/08/18 17:59:34 by aguemazi         ###   ########.fr       */
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

int	LAST_RETURN;

int		ft_get_indice_variable(char *env[], char *variable);
char	*test(char *str, char *env[]);
int		ft_exec_path(char **command_split, char *env[]);
void	ft_free_doublechar(char ***tab);
char	**ft_split_minishell(char *s);
char	*ft_add_str_in_str(char *s1, char *s2, int begin);
char	*ft_delete_nchar(char *str, int begin, int n);
char	*ft_expand_string_variables(char *str, char *env[], size_t begin,
			size_t n);

#endif