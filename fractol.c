/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:40:31 by ataher            #+#    #+#             */
/*   Updated: 2024/11/19 09:42:11 by ataher           ###   ########.fr       */
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
	int iteration = 0;
	long double zReal = 0.0;
	long double zImag = 0.0;
	long double tempReal;

	while (iteration < data->max_iterations)
	{
		tempReal = zReal;
		zReal = tempReal * tempReal - zImag * zImag + x;
		zImag = 2.0 * tempReal * zImag + y;

		iteration++;

		if (zReal * zReal + zImag * zImag > 4)
		{
			double smooth = iteration + 1 - log(log(sqrt(zReal * zReal + zImag * zImag))) / log(2);
			int red   = (int)(smooth * 15) % 256;
			int green = (int)(smooth * 10) % 256;
			int blue  = (int)(smooth * 15) % 256;
			*pixel = (red << 16) | (green << 8) | blue;

			if (pixel_bits != 32)
				*pixel = mlx_get_color_value(data->mlx, *pixel);
			return;
		}
	}
	*pixel = 0x000000;
	if (pixel_bits != 32)
		*pixel = mlx_get_color_value(data->mlx, *pixel);
}

void calc_pixel_julia(t_data *data, long double zReal, long double zImag, int *pixel, int pixel_bits)
{
	int iteration = 0;
	long double tempReal;

	while (iteration < data->max_iterations)
	{
		tempReal = zReal;
		zReal = tempReal * tempReal - zImag * zImag + data->julia[0];
		zImag = 2.0 * tempReal * zImag + data->julia[1];

		iteration++;

		if (zReal * zReal + zImag * zImag > 4)
		{
			double smooth = iteration + 1 - log(log(sqrt(zReal * zReal + zImag * zImag))) / log(2);
			int red   = (int)(smooth * 15) % 256;
			int green = (int)(smooth * 10) % 256;
			int blue  = (int)(smooth * 15) % 256;
			*pixel = (red << 16) | (green << 8) | blue;

			if (pixel_bits != 32)
				*pixel = mlx_get_color_value(data->mlx, *pixel);
			return;
		}
	}
	*pixel = 0x000000;
	if (pixel_bits != 32)
		*pixel = mlx_get_color_value(data->mlx, *pixel);
}

void	paint_canvas(t_data *data)
{
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer = mlx_get_data_addr(data->image, &pixel_bits, &line_bytes, &endian);

	int i = 0;
	while (i < WIDTH * HEIGHT)
	{
		long double x = 0.0;
		long double y = 0.0;
		set_coordinates(&x, &y, i, data->position, data->zoom_level);

		if (data->type == 0)
			calc_pixel_mandelbrot(data, x, y, (int *)(buffer + i * (pixel_bits / 8)), pixel_bits);
		else if (data->type == 1)
			calc_pixel_julia(data, x, y, (int *)(buffer + i * (pixel_bits / 8)), pixel_bits);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}
