/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:13:44 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/16 10:16:43 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

size_t	iterate_fractal(t_complex z, t_complex c, t_specs *specs)
{
	size_t	iteration;

	iteration = 0;
	while (iteration < specs->max_iteration)
	{
		if (cmagn(z) >= specs->threshold)
			break ;
		if (specs->type == MANDLEBROT)
			z = mandelbrot(z, c, specs);
		else if (specs->type == JULIA)
			z = julia(z, specs->c, specs);
		else if (specs->type == BURNING_SHIP)
			z = burning_ship(z, c, specs);
		iteration++;
	}
	return (iteration);
}

void	draw_pixel(float i, float j, t_specs *specs)
{
	t_complex	c;
	t_complex	z;

	if (specs->type == JULIA)
	{
		c.a = 0;
		c.b = 0;
		z.a = (i - specs->x_offset - specs->width / 2) * specs->scale;
		z.b = (j - specs->y_offset - specs->height / 2) * specs->scale;
	}
	else
	{
		c.a = (i - specs->x_offset) - specs->width / 2;
		c.b = (j - specs->y_offset) - specs->height / 2;
		z.a = 0;
		z.b = 0;
	}
	set_pixel(&specs->img, i, j, compute_color(specs->colors, \
			iterate_fractal(z, c, specs), specs->max_iteration));
}

void	draw_fractal(t_specs *specs)
{
	float		i;
	float		j;

	j = 0;
	i = 0;
	while (j < specs->height)
	{
		i = 0;
		while (i < specs->width)
		{
			draw_pixel(i, j, specs);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(specs->mlx, specs->mlx_win, specs->img.img, 0, 0);
}

void	set_fractal(int argc, char **argv, t_specs *specs)
{
	if (argc == 1)
	{
		ft_printf("options:\n(1) mandlebrot\n(2) julia\n(3) burning ship\n");
		exit(0);
	}
	if (ft_strncmp(argv[1], "1", 2) == 0)
	{
		specs->title = "mandelbrot";
		specs->type = MANDLEBROT;
	}
	else if (ft_strncmp(argv[1], "2", 2) == 0)
	{
		specs->title = "julia";
		specs->type = JULIA;
	}
	else if (ft_strncmp(argv[1], "3", 2) == 0)
	{
		specs->title = "burning ship";
		specs->type = BURNING_SHIP;
	}
	else
	{
		ft_printf("options:\n(1) mandlebrot\n(2) julia\n(3) burning ship\n");
		exit(0);
	}
}
