/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:40:31 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 03:16:03 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	set_coordinates(t_complex *point, int pp, long double cp[2], double zl)
{
	point->real = (pp % WIDTH) - (WIDTH / 2);
	point->imag = (pp / WIDTH) - (HEIGHT / 2);
	point->imag *= -1;
	point->real /= zl;
	point->imag /= zl;
	point->real += cp[0];
	point->imag += cp[1];
}

void	calc_pixel_mandelbrot(t_data *data, t_calc_pixel_fractol params)
{
	int			iteration;
	t_complex	z;
	t_complex	c;
	t_complex	center;

	z.real = 0;
	z.imag = 0;
	center.real = 0;
	center.imag = 0;
	c = params.point;
	iteration = 0;
	while (iteration < data->max_iterations)
	{
		z = complex_number_add(complex_number_squared(z), c);
		iteration++;
		if (complex_get_distance(z, center) > 2)
		{
			*params.pixel = calc_color(data, z, iteration, params.pb);
			return ;
		}
	}
	*params.pixel = 0x000000;
	if (params.pb != 32)
		*params.pixel = mlx_get_color_value(data->mlx, *params.pixel);
}

void	calc_pixel_julia(t_data *data, t_calc_pixel_fractol params)
{
	int			iteration;
	t_complex	z;
	t_complex	c;
	t_complex	center;

	z = params.point;
	center.real = 0;
	center.imag = 0;
	c.real = data->julia[0];
	c.imag = data->julia[1];
	iteration = 0;
	while (iteration < data->max_iterations)
	{
		z = complex_number_add(complex_number_squared(z), c);
		iteration++;
		if (complex_get_distance(z, center) > 2)
		{
			*params.pixel = calc_color(data, z, iteration, params.pb);
			return ;
		}
	}
	*params.pixel = 0x000000;
	if (params.pb != 32)
		*params.pixel = mlx_get_color_value(data->mlx, *params.pixel);
}

/*
	newton's fractal
	f(z) = z^3 - 1
	f'(z) = 3z^2
*/
void	calc_pixel_newton(t_data *data, t_calc_pixel_fractol params)
{
	int			iteration;
	t_complex	z;
	t_rgb		color;

	z = params.point;
	iteration = 0;
	while (iteration < data->max_iterations)
	{
		z = calc_newtons_method(z);
		color = calc_newton_color(z);
		*params.pixel = (color.red << 16) | (color.green << 8) | color.blue;
		if (params.pb != 32)
			*params.pixel = mlx_get_color_value(data->mlx, *params.pixel);
		if (color.red != 0 || color.green != 0 || color.blue != 0)
			return ;
		iteration++;
	}
	*params.pixel = 0x000000;
	if (params.pb != 32)
		*params.pixel = mlx_get_color_value(data->mlx, *params.pixel);
}
