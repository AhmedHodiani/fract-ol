/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:33:14 by ataher            #+#    #+#             */
/*   Updated: 2024/11/19 12:22:44 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <X11/keysym.h>
#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"

#define WIDTH 1000
#define HEIGHT 800

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*image;
	double	zoom_level;
	long double	position[2];
	int max_iterations;
	int type; // 0 = mandelbrot, 1 = julia, // 2 = newton
	long double julia[2];
} t_data;

typedef struct s_complex
{
	long double real;
	long double imag;
} t_complex;

int		key_hook(int keycode, t_data *data);
int		mouse_hook(int button, int x, int y, t_data *data);
void	ft_destory(t_data *data);
void	paint_canvas(t_data *data);

// complex related shit:
t_complex	complex_number_cubed(t_complex z);
t_complex	complex_number_squared(t_complex z);
t_complex	complex_number_add(t_complex z1, t_complex z2);
t_complex	complex_number_subtract(t_complex z1, t_complex z2);
t_complex	complex_number_divide(t_complex z1, t_complex z2);
void		complex_get_roots_of_unity(t_complex roots[3]);
long double	complex_get_distance(t_complex z1, t_complex z2);

// utils
int	calc_color(t_data *data, t_complex z, int iteration, int pixel_bits);

#endif
