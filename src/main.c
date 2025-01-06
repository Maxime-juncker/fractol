/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:17:47 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/06 09:56:33 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_specs	setup_specs(int width, int height)
{
	t_specs	specs;

	specs.width = width;
	specs.height = height;
	specs.scale = .005f;
	specs.x_offset = 0;
	specs.y_offset = 0;
	specs.threshold = 2;
	specs.max_iteration = 50;
	specs.nb_symetries = 2;
	set_color_palette(0, &specs);
	specs.c.a = 0.285;
	specs.c.b = 0.01;
	return (specs);
}

int	destroy(t_specs *specs)
{
	if (specs->mlx == NULL)
		exit(1);
	if (specs->img.img)
		mlx_destroy_image(specs->mlx, specs->img.img);
	if (specs->mlx_win)
		mlx_destroy_window(specs->mlx, specs->mlx_win);
	mlx_destroy_display(specs->mlx);
	free(specs->mlx);
	exit(0);
}

void	init_mlx(t_specs *specs)
{
	specs->mlx = mlx_init();
	if (specs->mlx == NULL)
		exit(1);
	specs->mlx_win = mlx_new_window(specs->mlx, specs->width, \
	specs->height, specs->title);
	if (specs->mlx_win == NULL)
		destroy(specs);
	specs->img.img = mlx_new_image(specs->mlx, specs->width, specs->height);
	if (specs->img.img == NULL)
		destroy(specs);
	specs->img.addr = mlx_get_data_addr(specs->img.img, \
	&specs->img.bits_per_pixel, &specs->img.line_length, &specs->img.endian);
	if (specs->img.addr == NULL)
		destroy(specs);
	mlx_key_hook(specs->mlx_win, handle_key_event, specs);
	mlx_mouse_hook(specs->mlx_win, handle_mouse_event, specs);
	mlx_hook(specs->mlx_win, 17, 1L << 2, destroy, specs);
}

int	main(int argc, char **argv)
{
	t_specs	specs;

	specs = setup_specs(720, 480);
	set_fractal(argc, argv, &specs);
	if (argc == 4)
	{
		specs.c.a = (double)ft_atoi(argv[2]) / 100;
		specs.c.b = (double)ft_atoi(argv[3]) / 100;
	}
	init_mlx(&specs);
	draw_fractal(&specs);
	mlx_loop(specs.mlx);
}
