/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:40:31 by ataher            #+#    #+#             */
/*   Updated: 2024/11/19 12:48:23 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

void	set_coordinates(long double *x, long double *y, int pixel_postion, long double center_position[2], double zoom_level)
{
	*x = (pixel_postion % WIDTH) - (WIDTH / 2);
	*y = (pixel_postion / WIDTH) - (HEIGHT / 2);
	*y *= -1;

	*x /= zoom_level;
	*y /= zoom_level;

	*x += center_position[0];
	*y += center_position[1];
}

void calc_pixel_mandelbrot(t_data *data, long double x, long double y, int *pixel, int pixel_bits)
{
	int iteration;
	t_complex z;
	t_complex c;
	t_complex center;

	z.real = 0;
	z.imag = 0;
	center.real = 0;
	center.imag = 0;
	c.real = x;
	c.imag = y;
	iteration = 0;
	while (iteration < data->max_iterations)
	{
		z = complex_number_add(complex_number_squared(z), c);
		iteration++;
		if (complex_get_distance(z, center) > 2)
		{
			*pixel = calc_color(data, z, iteration, pixel_bits);
			return;
		}
	}
	*pixel = 0x000000;
	if (pixel_bits != 32)
		*pixel = mlx_get_color_value(data->mlx, *pixel);
}

void calc_pixel_julia(t_data *data, long double zReal, long double zImag, int *pixel, int pixel_bits)
{
	int iteration;
	t_complex z;
	t_complex c;
	t_complex center;

	z.real = zReal;
	z.imag = zImag;
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
			*pixel = calc_color(data, z, iteration, pixel_bits);
			return;
		}
	}
	*pixel = 0x000000;
	if (pixel_bits != 32)
		*pixel = mlx_get_color_value(data->mlx, *pixel);
}

void	calc_pixel_newton(t_data *data, long double x, long double y, int *pixel, int pixel_bits)
{
	// newton's fractal
	// f(z) = z^3 - 1
	// f'(z) = 3z^2

	int iteration = 0;
	t_complex z;
	z.real = x;
	z.imag = y;

	t_complex roots[3];
	complex_get_roots_of_unity(roots);

	while (iteration < data->max_iterations)
	{
		t_complex f = complex_number_cubed(z);
		f.real -= 1.0;

		t_complex df = complex_number_squared(z);
		df.real = df.real * 3;
		df.imag = df.imag * 3;

		z = complex_number_subtract(z, complex_number_divide(f, df));

		int i = 1;
		while (i < 4)
		{
			long double distance = complex_get_distance(z, roots[i - 1]);
			if (distance < 0.1)
			{
				int red   = (int)(i * 70) % 256;
				int green = (int)(i * 40) % 256;
				int blue  = (int)(i * 50) % 256;
				*pixel = (red << 16) | (green << 8) | blue;

				if (pixel_bits != 32)
					*pixel = mlx_get_color_value(data->mlx, *pixel);
				return;
			}
			i++;
		}
		iteration++;
	}
	*pixel = 0x000000;
	if (pixel_bits != 32)
		*pixel = mlx_get_color_value(data->mlx, *pixel);
}
