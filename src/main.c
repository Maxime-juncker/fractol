#include <mlx.h>
#include <libft.h>
#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>

typedef enum e_fractal
{
	NONE,
	MANDLEBROT,
	JULIA,
	BURNING_SHIP
} t_fractal;

typedef	struct s_colors
{
	int r;
	int g;
	int b;
	float power;
} t_colors;

typedef struct s_specs
{
	size_t	width;
	size_t	height;
	char *title;

	void	*mlx;
	void	*mlx_win;

	t_colors colors;

	t_fractal	type;
	float scale;
	int x_offset;
	int y_offset;
	float	threshold;

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


void	set_color_palette(int id, t_specs *specs)
{
	// 0 = default
	if (id == 0)
	{
		specs->colors.r = 200;
		specs->colors.g = 200;
		specs->colors.b = 200;
		specs->colors.power = 1.3f;
	}
	if (id == 1)
	{
		specs->colors.r = 150;
		specs->colors.g = 50;
		specs->colors.b = 255;
		specs->colors.power = 1.4f;
	}
	if (id == 2)
	{
		specs->colors.r = 50;
		specs->colors.g = 20;
		specs->colors.b = 255;
		specs->colors.power = 1.4f;
	}
}

int	compute_color(t_colors colors, int iteration, int max_iteration)
{
	int	r;
	int	g;
	int	b;

	r = colors.r * iteration / max_iteration * colors.power;
	g = colors.g * iteration / max_iteration * colors.power;
	b = colors.b * iteration / max_iteration * colors.power;
	return create_trgb(0, r, g, b);
}

double complex mandelbrot(double complex z, double complex c, t_specs *specs)
{
	return (z*z + c * specs->scale);
}

double complex julia(double complex z, double complex c, t_specs *specs)
{
	(void)specs;
	return (z*z*z*z*z + c);
}

double complex burning_ship(double complex z, double complex c, t_specs *specs)
{
	return ((fabs(creal(z)) + I*fabs(cimag(z)))*(fabs(creal(z)) + I*fabs(cimag(z))) + c * specs->scale);
}

void	draw_fractal(t_specs *specs)
{
	t_data	img;

	img.img = mlx_new_image(specs->mlx, specs->width, specs->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	float i = 0;
	float j = 0;
	size_t iteration = 0;
	size_t max_iteration = 30;
	double complex c;
	double complex z;

	while (j < specs->height)
	{
		i = 0;
		while (i < specs->width)
		{
			if (specs->type == MANDLEBROT)
			{
				c = ((i - specs->x_offset) - specs->width / 2) + ((j - specs->y_offset) - specs->height / 2) * I;
				z = 0;
			}
			else if (specs->type == JULIA)
			{
				c = 0.8 + 0.6 * I;
				z = (((i - specs->x_offset) - specs->width / 2)* specs->scale) + (((j - specs->y_offset) - specs->height / 2) * I* specs->scale);
			}
			else
			{
				z = 0;
				c = ((i - specs->x_offset) - specs->width / 2) + ((j - specs->y_offset) - specs->height / 2) * I;
			}
			iteration = 0;
			while (iteration < max_iteration)
			{
				if (cabs(z) >= specs->threshold)
					break;
				if (specs->type == MANDLEBROT)
					z = mandelbrot(z, c, specs);
				else if (specs->type == JULIA)
					z = julia(z, c, specs);
				else if (specs->type == BURNING_SHIP)
					z = burning_ship(z, c, specs);
				iteration++;
			}
			set_pixel(&img, i, j, compute_color(specs->colors ,iteration, max_iteration));
			i++;
		}
		j++;
	}
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
		specs->scale -= .05f * specs->scale;

		// specs->x_offset -= x / 5 - specs->width / 10;
		// specs->y_offset -= y / 3 - specs->height / 10;
	}
	if (button == 5)
	{
		specs->scale += .05f * specs->scale;

		// specs->x_offset += x / 5 - specs->width / 10;
		// specs->y_offset += y / 3 - specs->height / 10;
	}
	draw_fractal(specs);
	return 0;
}

int	handle_key_event(int code, t_specs *specs)
{
	if (specs == NULL)
		return (-1);
	if (code == 'q')
	{
		mlx_destroy_window(specs->mlx, specs->mlx_win);
		exit(0);
	}
	else if (code == 'a')
		specs->x_offset += 60;
	else if (code == 'd')
		specs->x_offset -= 60;
	else if (code == 'w')
		specs->y_offset += 60;
	else if (code == 's')
		specs->y_offset -= 60;
	else if (code == 'r')
	{
		specs->x_offset = 0;
		specs->y_offset = 0;
		specs->scale = 0.005f;
	}

	// colors
	else if (code == '1')
		set_color_palette(0, specs);
	else if (code == '2')
		set_color_palette(1, specs);
	else if (code == '3')
		set_color_palette(2, specs);
	else
		return (0);
	draw_fractal(specs);
	return (0);
}

void	menu(t_specs *specs)
{
	(void)specs;
	char	buff[20];
	ft_printf("Choose your fractal:\n(0) exit\n(1) mandlebrot\n(2) julia\n(3) burning ship\n");
	read(0, buff, 1);
	if (buff[0] == '0')
		exit(0);
	if (buff[0] == '1')
	{
		specs->title = "mandelbrot";
		specs->type = MANDLEBROT;
	}
	else if(buff[0] == '2')
	{
		specs->title = "julia";
		specs->type = JULIA;
	}
	else if (buff[0] == '3')
	{
		specs->title = "burning ship";
		specs->type = BURNING_SHIP;
	}
	else
	{
		ft_printf("\nWrong input, please try again\n");
		menu(specs);
	}

}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_specs	specs;

	specs.width = 720;
	specs.height = 480;
	specs.title = "Default";
	specs.type = JULIA;

	specs.scale = .005f;
	specs.x_offset = 0;
	specs.y_offset = 0;
	specs.threshold = 2;
	set_color_palette(0, &specs);

	menu(&specs);

	specs.mlx = mlx_init();
	specs.mlx_win = mlx_new_window(specs.mlx, specs.width, specs.height, specs.title);

	mlx_key_hook(specs.mlx_win, handle_key_event, &specs);
	mlx_mouse_hook(specs.mlx_win, handle_mouse_event, &specs);
	draw_fractal(&specs);

	mlx_loop(specs.mlx);
}