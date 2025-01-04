/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:43:40 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 03:16:04 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	paint_canvas(t_data *data)
{
	int						line_bytes;
	int						endian;
	int						i;
	char					*buffer;
	t_calc_pixel_fractol	params;

	buffer = mlx_get_data_addr(data->image, &params.pb, &line_bytes, &endian);
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		params.point.real = 0.0;
		params.point.imag = 0.0;
		params.pixel = (int *)(buffer + i * (params.pb / 8));
		set_coordinates(&params.point, i, data->position, data->zoom_level);
		if (data->type == 0)
			calc_pixel_mandelbrot(data, params);
		else if (data->type == 1)
			calc_pixel_julia(data, params);
		else if (data->type == 2)
			calc_pixel_newton(data, params);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}

int	init_fractol_type(t_data *data, int argc, char **argv)
{
	if (argc < 2 || argc > 4)
	{
		send_parameters_missing();
		return (0);
	}
	if (!ft_strcmp(argv[1], "mandelbrot"))
		data->type = 0;
	else if (!ft_strcmp(argv[1], "julia"))
		data->type = 1;
	else if (!ft_strcmp(argv[1], "newton"))
		data->type = 2;
	else
	{
		send_fractol_type_is_not_valid(argv[1]);
		return (0);
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (data->type == 1)
	{
		if (argc != 4)
		{
			send_parameters_missing();
			return (0);
		}
		if (!is_valid_double(argv[2]) || !is_valid_double(argv[3]))
		{
			send_numbers_are_not_valid(argv[2], argv[3]);
			return (0);
		}
		data->julia[0] = ft_atof(argv[2]);
		data->julia[1] = ft_atof(argv[3]);
		data->max_iterations = 30;
	}
	else if ((data->type == 0 || data->type == 2) && argc != 2)
	{
		send_parameters_missing();
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.zoom_level = 200;
	data.max_iterations = 30;
	data.position[0] = 0;
	data.position[1] = 0;
	if (!init_fractol_type(&data, argc, argv) || !init_data(&data, argc, argv))
		return (1);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "ataher");
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.window || !data.image)
	{
		ft_destory(&data);
		return (1);
	}
	paint_canvas(&data);
	mlx_mouse_hook(data.window, mouse_hook, &data);
	mlx_key_hook(data.window, key_hook, &data);
	mlx_hook(data.window, 17, 0, &mlx_loop_end, data.mlx);
	mlx_loop(data.mlx);
	ft_destory(&data);
	return (0);
}
