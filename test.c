/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:41:36 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/08 15:42:59 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*\*/

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int count;

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return i;
}

void b(long int nb, char *str, int size)
{
	char c;
	if(nb >= size)
	{
		b(nb/size,str,size);
	}
	c = str[nb % size];
	write(1, &c, 1);
	count++;
}

void e(unsigned long int nb, char *str, int size)
{
	char c;
	if(nb >= size)
	{
		e(nb/size,str,size);
	}
	c = str[nb % size];
	write(1, &c, 1);
	count++;
}

int ft_printf(char *fmt, ...)
{
		count = 0;
        va_list ap;
		int i;
        long int d, x;
        char *s;        
		va_start(ap, fmt);
		i = 0;
        while (fmt[i])
        if(fmt[i] == '%')
		{
			i++;
            if(fmt[i] == 's')
			{
            	s = va_arg(ap, char *);
            	int i = 0;
				while (s[i])
				{
					write(1,&s[i],1);
				}
				i++;
			}                      /* string */
            else if(fmt[i] == 'd')
			{                     /* int */
                d = va_arg(ap, int);
				if (d<0)
				{
					d = -d;
					write(1,"-",1);
					count++;
				}
                b(d,"0123456789", 10);
				i++;
			}
            else if(fmt[i] == 'x')
			{                   /* char */
                       /* Note: char is promoted to int. */
            	x = va_arg(ap, long int);
                e(x,"0123456789ABCDEF", 16);
				i++;
			}
        }
		else
		{
			write(1,&fmt[i],1);
			i++;
			count++;
		}
        va_end(ap);
		return count;
}
/**/
int main ()
{
	ft_printf("test %d",-2147483648);
}
