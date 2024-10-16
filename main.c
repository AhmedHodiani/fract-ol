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
#include <math.h>

#define WIDTH 1000
#define HEIGHT 800

typedef struct s_data
{
	void	*mlx;
	void	*window;
	double	zoom_level;
	int		position[2];
} t_data;

typedef struct s_pixel
{
	int	color;
} t_pixel;

void	set_coordinates(double *x, double *y, int pixel_postion, int center_position[2], double zoom_level)
{
	*x = pixel_postion % WIDTH - WIDTH / 2 + center_position[0];
	*y = pixel_postion / WIDTH - HEIGHT / 2 + center_position[1];
	*y *= -1;

	*x /= zoom_level;
	*y /= zoom_level;
}

void	reset_coordinates(double *x, double *y, int center_position[2], double zoom_level)
{
	*x *= zoom_level;
	*y *= zoom_level;

	*y *= -1;
	*x += WIDTH / 2 - center_position[0];
	*y += HEIGHT / 2 - center_position[1];
}

void calc_pixel(t_data *data, double x, double y, t_pixel *pixel)
{
    // Example condition for coloring based on position (x == 2 or x == -2)
    if (x == 2 || x == -2)
    {
        pixel->color = 0x00FF00; // Green for specific condition
        return;
    }

    int iteration = 0;
    double zReal = 0.0;
    double zImag = 0.0;
    double tempReal;
    int max_iterations = 50;

    while (iteration < max_iterations)
    {
        // Save the current value of zReal before updating it
        tempReal = zReal;

        // Mandelbrot calculation: z = z^2 + c (where c is the point (x, y))
        zReal = tempReal * tempReal - zImag * zImag + x;
        zImag = 2.0 * tempReal * zImag + y;

        iteration++;

        // Check if point has "escaped" (distance from origin > 2)
        if (zReal * zReal + zImag * zImag > 4)
        {
            // Use a multi-color gradient based on the number of iterations
            int red   = (iteration * 15) % 256;  // Cycle red channel from 0 to 255
            int green = (iteration * 5) % 256; // Cycle green channel from 0 to 255
            int blue  = (iteration * 10) % 256; // Cycle blue channel from 0 to 255

            pixel->color = (red << 16) | (green << 8) | blue;  // Combine RGB into a single color value
            return;
        }
    }

    // If max iterations are reached, color as part of the Mandelbrot set
    pixel->color = 0x000000;  // Black for points inside the set
}


void	paint_canvas(t_data *data)
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

int	key_hook(int keycode, t_data *data)
{
	int moving_interval = 100;

	if (keycode == 119 || keycode == 65362)
		data->position[1] -= moving_interval;
	if (keycode == 115 || keycode == 65364)
		data->position[1] += moving_interval;
	if (keycode == 97 || keycode == 65361)
		data->position[0] -= moving_interval;
	if (keycode == 100 || keycode == 65363)
		data->position[0] += moving_interval;

	// printf("key pressed: %d\n", keycode);
	mlx_clear_window(data->mlx, data->window);
	paint_canvas(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	// if (data->zoom_level == 0.5 && button == 4)
	// 	return 0;

	if (data->zoom_level == 100 && button == 5)
		return 0;

	if (button == 4)
	{
		// data->position[0] = x - WIDTH / 2;
		// data->position[1] = y - HEIGHT / 2;
		data->zoom_level += 100;
	}
	if (button == 5)
	{
		// data->position[0] -= x - WIDTH / 2;
		// data->position[1] -= y - HEIGHT / 2;
		data->zoom_level -= 100;
	}

	// printf("Mouse button pressed: %d at (%d, %d), %f\n", button, x, y, data->zoom_level);
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
	data.position[0] = 0;
	data.position[1] = 0;


	paint_canvas(&data);


	mlx_mouse_hook(data.window, mouse_hook, &data);
	mlx_key_hook(data.window, key_hook, &data);
	mlx_loop(data.mlx);

	return (0);
}

// cc main.c -lm -Lminilibx-linux -lmlx_Linux -lX11 -lXext && ./a.out