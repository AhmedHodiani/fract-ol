/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:43:40 by ataher            #+#    #+#             */
/*   Updated: 2024/11/19 09:46:19 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

int		main(int argc, char **argv)
{
	t_data data;
	data.zoom_level = 200;
	data.max_iterations = 30;
	data.position[0] = 0;
	data.position[1] = 0;

	if (argc < 2)
	{
		ft_printf("parameters missing\n");
		return 1;
	}
	if (!ft_strcmp(argv[1], "mandelbrot"))
	{
		data.type = 0;
	}
	else if (!ft_strcmp(argv[1], "julia"))
	{
		if (argc != 4) {
			ft_printf("wrong parameters\n");
			return 1;
		}
		data.julia[0] = ft_atof(argv[2]);
		data.julia[1] = ft_atof(argv[3]);

		data.type = 1;
		data.max_iterations = 30;
	}
	else {
		ft_printf("unknown fractol\n");
		return 1;
	}

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "ataher");
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);

	paint_canvas(&data);
	mlx_mouse_hook(data.window, mouse_hook, &data);
	mlx_key_hook(data.window, key_hook, &data);
	mlx_hook(data.window, 17, 0, &mlx_loop_end, data.mlx);
	mlx_loop(data.mlx);
	ft_destory(&data);
	return (0);
}

// cc main.c -lm -Lminilibx-linux -lmlx_Linux -lX11 -lXext && ./a.out
