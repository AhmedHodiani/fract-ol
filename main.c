/*
• open, close, read, write,
	malloc, free, perror,
	strerror, exit
• All functions of the math
	library (-lm compiler option,
	man 3 math)
• All functions of the MiniLibX
• ft_printf and any equivalent
	YOU coded
*/
#include "fractol.h"

#define WIDTH 800
#define HEIGHT 500

typedef struct s_data {
    void *mlx;
    void *window;
    double zoom_level;
	int position[2];
} t_data;

typedef struct s_pixel {
	int color;
} t_pixel;

void set_coordinates(double *x, double *y, int pixel_postion, int center_position[2], double zoom_level)
{
	*x = pixel_postion % WIDTH - WIDTH / 2 + center_position[0];
	*y = pixel_postion / WIDTH - HEIGHT / 2 + center_position[1];
	*y *= -1;

	*x *= zoom_level;
	*y *= zoom_level;
}

void reset_coordinates(double *x, double *y, int center_position[2], double zoom_level)
{
	*x /= zoom_level;
	*y /= zoom_level;

	*y *= -1;
	*x += WIDTH / 2 - center_position[0];
	*y += HEIGHT / 2 - center_position[1];
}

void calc_pixel(t_data *data, double x, double y, t_pixel *pixel)
{
	// if (y < 0)
	// {
	// 	pixel->color = 0x00FFFF;
	// }
	// if (x > 0)
	// {
	// 	pixel->color = 0xFFFFFF;
	// }
	if ((x)*(x) + (y) * (y) < 100 * 100)
	{
		pixel->color = 0x0000FF;
		// printf("x = %f, y = %f\n", x, y);
	}


	// if (x*x == y)
	// {
	// 	pixel->color = 0xFF0000;
	// }
}

void paint_canvas(t_data *data)
{
	t_pixel grid[WIDTH][HEIGHT] = {0};

	int i = 0;
	while (i < WIDTH * HEIGHT)
	{
		double x = 0.0;
		double y = 0.0;
		set_coordinates(&x, &y, i, data->position, data->zoom_level);
		// printf("%d => x = %f, y = %f\n", i, x, y);

		calc_pixel(data, x, y, &grid[i % WIDTH][i / WIDTH]);

		reset_coordinates(&x, &y, data->position, data->zoom_level);

		mlx_pixel_put(data->mlx, data->window, x, y, grid[(int)x][(int)y].color);
		i++;
	}
}

int key_hook(int keycode, t_data *data) {
	int moving_interval = 25;

	if (keycode == 119 || keycode == 65362)
		data->position[1] += moving_interval;
	else if (keycode == 115 || keycode == 65364)
		data->position[1] -= moving_interval;
	else if (keycode == 97 || keycode == 65361)
		data->position[0] += moving_interval;
	else if (keycode == 100 || keycode == 65363)
		data->position[0] -= moving_interval;

	printf("key pressed: %d\n", keycode);

	// mlx_clear_window(data->mlx, data->window);
	paint_canvas(data);
	return (0);
}

int mouse_hook(int button, int x, int y, t_data *data) {
	// if (data->zoom_level == 0.5 && button == 4)
	// 	return 0;

	if (button == 4)
		data->zoom_level -= 0.05;
	else if (button == 5)
		data->zoom_level += 0.05;


	printf("Mouse button pressed: %d at (%d, %d), %f\n", button, x, y, data->zoom_level);
	// mlx_clear_window(data->mlx, data->window);

	paint_canvas(data);
	return (0);
}

int main(void) {
	t_data data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "ataher");
	data.zoom_level = 4;
	data.position[0] = 0;
	data.position[1] = 0;


	paint_canvas(&data);


	mlx_mouse_hook(data.window, mouse_hook, &data);
	mlx_key_hook(data.window, key_hook, &data);
	mlx_loop(data.mlx);

	return (0);
}
