/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:30:48 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/06 09:49:58 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void	handle_movement(int code, t_specs *specs)
{
	if (code == 'a')
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
}

static void	handle_settings(int code, t_specs *specs)
{
	if (code == '=')
		specs->max_iteration += 10;
	else if (code == '-' && specs->max_iteration - 10 > 10)
		specs->max_iteration -= 10;
	else if (code == 'z')
		specs->threshold += 0.2f;
	else if (code == 'x' && specs->threshold > 0.2f)
		specs->threshold -= 0.2f;
	else if (code == 'e')
		specs->nb_symetries++;
	else if (code == 'f' && specs->nb_symetries > 2)
		specs->nb_symetries--;
}

int	handle_key_event(int code, t_specs *specs)
{
	if (specs == NULL)
		return (-1);
	if (code == 65307)
	{
		destroy(specs);
	}
	handle_movement(code, specs);
	handle_settings(code, specs);
	if (code == '1')
		set_color_palette(0, specs);
	else if (code == '2')
		set_color_palette(1, specs);
	else if (code == '3')
		set_color_palette(2, specs);
	draw_fractal(specs);
	return (0);
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
		specs->x_offset *= 1.05f;
		specs->y_offset *= 1.05f;
	}
	if (button == 5)
	{
		specs->scale += .05f * specs->scale;
		specs->x_offset *= 0.95f;
		specs->y_offset *= 0.95f;
	}
	draw_fractal(specs);
	return (0);
}
