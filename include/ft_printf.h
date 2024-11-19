/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:35:43 by ataher            #+#    #+#             */
/*   Updated: 2024/09/14 08:39:34 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);
int		ft_putaddress_fd(void *address, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_puthex_fd(unsigned int num, const char format, int fd);
int		ft_putunsigned_fd(unsigned int n, int fd);

// helpers
void	hp_puthex_fd(unsigned long num, const char format, int fd);
int		hp_putchar_fd(char c, int fd);
size_t	hp_hexlen(unsigned	long num);
size_t	hp_strlen(char const *s);

#endif
