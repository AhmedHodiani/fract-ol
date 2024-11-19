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

void calc_pixel(t_data *data, long double x, long double y, int *pixel, int pixel_bits)
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
			int color = (int)(255 * smooth / data->max_iterations);
			int red   = color % 256;
			int green = 60;
			int blue  = 90;
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

void	paint_canvas_mandelbrot(t_data *data)
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
		calc_pixel(data, x, y, (int *)(buffer + i * (pixel_bits / 8)), pixel_bits);

		i++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}

void paint_canvas_julia(t_data *data)
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
		calc_pixel(data, x, y, (int *)(buffer + i * (pixel_bits / 8)), pixel_bits);

		i++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
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

	printf("Position: %Lf, %Lf\n", data->position[0], data->position[1]);

	if (data->type == 0)
		paint_canvas_mandelbrot(data);
	else if (data->type == 1)
		paint_canvas_julia(data);
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
	if (button == 5 && data->zoom_level > 100)
		data->zoom_level *= 0.5;

	if (data->type == 0)
		paint_canvas_mandelbrot(data);
	else if (data->type == 1)
		paint_canvas_julia(data);
	return (0);
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putendl(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

// ft_strcmp
int ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}


int		main(int argc, char **argv)
{
	t_data data;
	data.zoom_level = 200;
	data.max_iterations = 19;
	data.position[0] = 0;
	data.position[1] = 0;

	if (argc < 2) {
		ft_putendl("parameters missing");
		return 1;
	}

	if (!ft_strcmp(argv[1], "mandelbrot"))
	{
		data.mlx = mlx_init();
		data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "ataher");
		data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
		data.type = 0;

		paint_canvas_mandelbrot(&data);
		mlx_mouse_hook(data.window, mouse_hook, &data);
		mlx_key_hook(data.window, key_hook, &data);
		mlx_loop(data.mlx);
	}
	else if (!ft_strcmp(argv[1], "julia"))
	{
		data.mlx = mlx_init();
		data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "ataher");
		data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
		data.type = 1;

		paint_canvas_julia(&data);
		mlx_mouse_hook(data.window, mouse_hook, &data);
		mlx_key_hook(data.window, key_hook, &data);
		mlx_loop(data.mlx);
	}
	else {
		ft_putendl("unknown fractol");
		return 1;
	}
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


