/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:33:14 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 03:15:28 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "libft.h"
# include "libftprintf.h"

# define WIDTH 500
# define HEIGHT 500

// type: 0 = mandelbrot, 1 = julia, // 2 = newton
typedef struct s_data
{
	void		*mlx;
	void		*window;
	void		*image;
	double		zoom_level;
	long double	position[2];
	int			max_iterations;
	int			type;
	long double	julia[2];
}	t_data;

typedef struct s_complex
{
	long double	real;
	long double	imag;
}	t_complex;

typedef struct s_calc_pixel_fractol
{
	t_complex	point;
	int			*pixel;
	int			pb;
}	t_calc_pixel_fractol;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

void		paint_canvas(t_data *data);
int			key_hook(int keycode, t_data *data);
int			mouse_hook(int button, int x, int y, t_data *data);
void		ft_destory(t_data *data);

//fractols
void		set_coordinates(t_complex *p, int pp, long double cp[2], double zl);
void		calc_pixel_mandelbrot(t_data *data, t_calc_pixel_fractol p);
void		calc_pixel_julia(t_data *data, t_calc_pixel_fractol p);
void		calc_pixel_newton(t_data *data, t_calc_pixel_fractol p);

// complex numbers related shit
t_complex	complex_number_cubed(t_complex z);
t_complex	complex_number_squared(t_complex z);
t_complex	complex_number_add(t_complex z1, t_complex z2);
t_complex	complex_number_subtract(t_complex z1, t_complex z2);
t_complex	complex_number_divide(t_complex z1, t_complex z2);
void		complex_get_roots_of_unity(t_complex roots[3]);
long double	complex_get_distance(t_complex z1, t_complex z2);

// utils
int			calc_color(t_data *data, t_complex z, int iteration, int pb);
void		send_parameters_missing(void);
void		send_fractol_type_is_not_valid(char *fractol_type);
void		send_numbers_are_not_valid(char *x, char *y);
int			is_valid_double(char *str);
t_complex	calc_newtons_method(t_complex z);
t_rgb		calc_newton_color(t_complex z);

#endif
