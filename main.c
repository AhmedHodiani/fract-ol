#include "fractol.h"

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

void	reset_coordinates(long double *x, long double *y, long double center_position[2], double zoom_level)
{
	*x -= center_position[0];
	*y -= center_position[1];

	*x *= zoom_level;
	*y *= zoom_level;

	*y *= -1;
	*x += WIDTH / 2;
	*y += HEIGHT / 2;
}

void calc_pixel(t_data *data, long double x, long double y, int *pixel)
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
			int red   = (iteration * 10) % 256;
			int green = (iteration * 15) % 256;
			int blue  = (iteration * 15) % 256;
			*pixel = (red << 16) | (green << 8) | blue;
			return;
		}
	}
	*pixel = 0x000000;
}

void	paint_canvas(t_data *data)
{
	int grid[WIDTH][HEIGHT] = {0};

	int i = 0;
	while (i < WIDTH * HEIGHT)
	{
		long double x = 0.0;
		long double y = 0.0;
		set_coordinates(&x, &y, i, data->position, data->zoom_level);
		calc_pixel(data, x, y, &grid[i % WIDTH][i / WIDTH]);
		reset_coordinates(&x, &y, data->position, data->zoom_level);
		mlx_pixel_put(data->mlx, data->window, x, y, grid[(int)x][(int)y]);
		i++;
	}
}

int	key_hook(int keycode, t_data *data)
{
	double moving_interval = 300 / data->zoom_level;

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
		data->max_iterations *= 0.5;

	// printf("key pressed: %d\n", keycode);
	mlx_clear_window(data->mlx, data->window);
	paint_canvas(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		data->zoom_level *= 3;
		data->position[0] += (x - WIDTH / 2) / data->zoom_level;
		data->position[1] += -(y - HEIGHT / 2) / data->zoom_level;
	}
	if (button == 5)
		data->zoom_level *= 0.5;

	mlx_clear_window(data->mlx, data->window);
	paint_canvas(data);
	return (0);
}

int	main(void)
{
	t_data data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "ataher");
	data.zoom_level = 200;
	data.max_iterations = 50;
	data.position[0] = 0;
	data.position[1] = 0;

	paint_canvas(&data);
	mlx_mouse_hook(data.window, mouse_hook, &data);
	mlx_key_hook(data.window, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}

// cc main.c -lm -Lminilibx-linux -lmlx_Linux -lX11 -lXext && ./a.out


/*
Whats left to do:
	- Fix the exit program
	- Fix the colors
	- Do the other fractolar (argc, argv)
*/


// keeps going to the center when I zoom
