/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:21:23 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/12 10:22:11 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	set_pixel(t_data *data, int x, int y, int color)
{
	void	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	set_color_palette(int id, t_specs *specs)
{
	if (id == 0)
	{
		specs->colors.r = 200;
		specs->colors.g = 200;
		specs->colors.b = 200;
		specs->colors.power = 1.3f;
	}
	if (id == 1)
	{
		specs->colors.r = 250;
		specs->colors.g = 250;
		specs->colors.b = 50;
		specs->colors.power = 1.3f;
	}
	if (id == 2)
	{
		specs->colors.r = 220;
		specs->colors.g = 20;
		specs->colors.b = 50;
		specs->colors.power = 1.5f;
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
	return (create_trgb(0, r, g, b));
}
