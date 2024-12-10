#include <mlx.h>
#include <libft.h>
#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <time.h>

typedef struct s_specs
{
	size_t	width;
	size_t	height;
	char *title;

	void	*mlx;
	void	*mlx_win;

	float scale;
	int x_offset;
	int y_offset;
} t_specs;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	set_pixel(t_data *data, int x, int y, int color)
{
	void	*dst;

	// a annoter
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	compute_color(int iteration, int max_iteration)
{
	int	r;
	int	g;
	int	b;

	r = 150 * iteration / max_iteration;
	g = 100 * iteration / max_iteration;
	b = 100;

	return create_trgb(0, r, g, b);
}


void	draw_fractal(t_specs *specs)
{
	t_data	img;
	time_t t;
	t = clock();
	static double full_time = 0;

	img.img = mlx_new_image(specs->mlx, specs->width, specs->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	float i = 0;
	float j = 0;
	size_t iteration = 0;
	size_t max_iteration = 30;
	float complex c;
	float complex z;

	int	threshold = 10;


	while (j < specs->height)
	{
		i = 0;
		while (i < specs->width)
		{
			c = (((i - specs->x_offset) - specs->width / 2)) + ((((j - specs->y_offset) - specs->height / 2) * I));
			z = 0;
			iteration = 0;
			while (iteration < max_iteration)
			{
				if (cabsf(z) >= threshold)
					break;
				z = z*z + c * specs->scale;
				iteration++;
			}
			set_pixel(&img, i, j, compute_color(iteration, max_iteration));
			i++;
		}
		j++;
	}
	t = clock() - t;
	 double time_taken = ((double)t)/CLOCKS_PER_SEC;
	 full_time += time_taken;
	printf("render time: %lf [full time]: %lf\n", time_taken, full_time);
	mlx_put_image_to_window(specs->mlx, specs->mlx_win, img.img, 0, 0);
}


int	handle_mouse_event(int button, int x, int y, t_specs *specs)
{
	(void)x;
	(void)y;
	if (specs == NULL)
		return (-1);
	if (button == 4)
	{
		specs->scale -= .0005f;
		// 	specs->x_offset -= x / 2;
		// specs->y_offset -= y / 2;
		draw_fractal(specs);
	}
	if (button == 5)
	{
		specs->scale += .0005f;
		// specs->x_offset -= x / 2;
		// specs->y_offset -= y / 2;
		draw_fractal(specs);
	}
	return 0;
}

int	handle_key_event(int code, t_specs *specs)
{
	if (specs == NULL)
		return (-1);
	ft_printf("code: %d\n", code);
	if (code == 'q')
	{
		mlx_destroy_window(specs->mlx, specs->mlx_win);
		exit(0);
	}

	if (code == 'a')
		specs->x_offset += 30;
	if (code == 'd')
		specs->x_offset -= 30;
	if (code == 'w')
		specs->y_offset += 30;
	if (code == 's')
		specs->y_offset -= 30;
	draw_fractal(specs);
	return (0);
}

int main(void)
{
	t_specs	specs;

	specs.width = 1920;
	specs.height = 1080;
	specs.title = "HAAAAAA";

	specs.scale = .005f;
	specs.x_offset = 0;
	specs.y_offset = 0;

	specs.mlx = mlx_init();
	specs.mlx_win = mlx_new_window(specs.mlx, specs.width, specs.height, specs.title);

	mlx_key_hook(specs.mlx_win, handle_key_event, &specs);
	mlx_mouse_hook(specs.mlx_win, handle_mouse_event, &specs);
	draw_fractal(&specs);

	mlx_loop(specs.mlx);
}