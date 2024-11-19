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

int	key_hook(int keycode, t_data *data)
{
	double moving_interval = 300 / data->zoom_level;

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
	long double lx = (long double)x;
	long double ly = (long double)y;

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
	}
	if (button == 5 && data->zoom_level > 150)
		data->zoom_level *= 0.5;

	paint_canvas(data);
	return (0);
}


void ft_destory(t_data *data)
{
	mlx_destroy_image(data->mlx, data->image);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

int		main(int argc, char **argv)
{
	t_data data;
	data.zoom_level = 200;
	data.max_iterations = 30;
	data.position[0] = 0;
	data.position[1] = 0;

	if (argc < 2)
	{
		ft_putendl_fd("parameters missing", 1);
		return 1;
	}
	if (!ft_strcmp(argv[1], "mandelbrot"))
	{
		data.type = 0;
	}
	else if (!ft_strcmp(argv[1], "julia"))
	{
		if (argc != 4) {
			ft_putendl_fd("wrong parameters", 1);
			return 1;
		}
		data.julia[0] = ft_atof(argv[2]);
		data.julia[1] = ft_atof(argv[3]);

		data.type = 1;
		data.max_iterations = 30;
	}
	else {
		ft_putendl_fd("unknown fractol", 1);
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
