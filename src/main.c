/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:17:47 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/12 11:14:14 by mjuncker         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_specs	specs;

	specs = setup_specs(720, 480);
	set_fractal(argc, argv, &specs);
	if (argc == 4)
	{
		specs.c.a = (double)atoi(argv[2]) / 100;
		specs.c.b = (double)atoi(argv[3]) / 100;
	}
	specs.mlx = mlx_init();
	specs.mlx_win = mlx_new_window(specs.mlx, specs.width, \
	specs.height, specs.title);
	specs.img.img = mlx_new_image(specs.mlx, specs.width, specs.height);
	specs.img.addr = mlx_get_data_addr(specs.img.img, \
	&specs.img.bits_per_pixel, &specs.img.line_length, &specs.img.endian);
	mlx_key_hook(specs.mlx_win, handle_key_event, &specs);
	mlx_mouse_hook(specs.mlx_win, handle_mouse_event, &specs);
	draw_fractal(&specs);
	mlx_loop(specs.mlx);
}
