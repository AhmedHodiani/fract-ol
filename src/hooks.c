/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:34:57 by ataher            #+#    #+#             */
/*   Updated: 2024/11/24 09:50:10 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	key_hook(int keycode, t_data *data)
{
	double	moving_interval;

	moving_interval = 300 / data->zoom_level;
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx);
	if (keycode == 119 || keycode == 65362)
		data->position[1] += moving_interval;
	if (keycode == 115 || keycode == 65364)
		data->position[1] -= moving_interval;
	if (keycode == 97 || keycode == 65361)
		data->position[0] -= moving_interval;
	if (keycode == 100 || keycode == 65363)
		data->position[0] += moving_interval;
	if (keycode == 61)
		data->max_iterations *= 1.5;
	if (keycode == 45 && data->max_iterations > 5)
		data->max_iterations *= 0.75;
	paint_canvas(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	long double	lx;
	long double	ly;

	lx = (long double)x;
	ly = (long double)y;
	if (button == 4)
	{
		lx -= (WIDTH / 2);
		ly -= (HEIGHT / 2);
		ly *= -1;
		lx /= data->zoom_level;
		ly /= data->zoom_level;
		data->position[0] += lx;
		data->position[1] += ly;
		data->zoom_level *= 3;
		data->max_iterations += 2;
	}
	if (button == 5 && data->zoom_level > 150)
	{
		data->zoom_level *= 0.5;
		data->max_iterations -= 2;
	}
	paint_canvas(data);
	return (0);
}

void	ft_destory(t_data *data)
{
	mlx_destroy_image(data->mlx, data->image);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
