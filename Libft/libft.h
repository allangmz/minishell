/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:02:07 by aguemazi          #+#    #+#             */
/*   Updated: 2022/07/06 10:33:17 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 22
# endif

void	*ft_memset(void	*tab, int value, size_t count);
void	*ft_memmove(void *destination, const void *source, size_t size);
void	*ft_memchr(const void *src, int search, size_t size);
void	ft_bzero(void *tab, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t count);
void	*ft_memccpy(void *dst, void *src, int ch, size_t size);
int		ft_memcmp(const void *src1, const void *src2, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, const char *src, unsigned int nb);
char	*ft_strchr(const char *str, int search);
char	*ft_strrchr(const char *str, int search);
char	*ft_strnstr(const char *str, const char *to_find, size_t size);
char	*ft_strstr(char *str, char *to_find);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
char	*ft_substr(char const *src, unsigned int start, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *str, ...);
/** ############### printf fonction ################### **/
int		ft_printf_c_value(va_list ptr);
int		ft_printf_d_or_i_value(int nbr);
int		ft_printf_p_value(va_list ptr);
int		ft_printf_percent_value(void);
int		ft_printf_s_value(va_list ptr);
void	ft_printf_putnbr_base2(unsigned long int nbr, const char *base, int *i);
void	ft_printf_putnbr_base(unsigned int nbr, const char *base, int *i);
void	ft_printf_putuns_fd(unsigned int nbr, int fd, int *i);
/** ################################################### **/
char	*get_next_line(int fd);
/** ############ get_next_line fonction ############### **/
char	*ft_get_next_line_strjoin(char *s1, char *s2);
char	*ft_get_next_line_line(char *line, char *buffer, int octet, int fd);
/** ################################################### **/
#endif
