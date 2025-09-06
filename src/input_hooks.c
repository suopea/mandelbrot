/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:46:46 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 16:16:39 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	mouse_hook(
	mouse_key_t button, action_t action, modifier_key_t mods, void *input)
{
	t_data	*data;
	int		x;
	int		y;

	(void)mods;
	data = input;
	clear_screen(data);
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		new_location_from_center(data, x, y);
}

void	scroll_hook(double xdelta, double ydelta, void *input)
{
	t_data	*data;

	(void) xdelta;
	data = input;
	if (ydelta > 0)
	{
		data->waiting_to_zoom = 1;
		data->to_zoom_soon *= 1.0 / (SCROLL_AMOUNT + (ydelta / 10));
	}
	if (ydelta < 0 && data->scale < DEFAULT_SCALE)
	{
		data->to_zoom_soon *= (SCROLL_AMOUNT - (ydelta / 50));
		if (data->waiting_to_zoom == 0)
		{
			get_cursor_location_and_zoom(data, data->to_zoom_soon);
			data->to_zoom_soon = 1;
		}
		else
		{
			data->waiting_to_zoom = 1;
		}
	}
}

static void	toggle_pause(t_data *data)
{
	if (data->paused)
		data->paused = false;
	else
		data->paused = true;
}

void	key_hook(mlx_key_data_t keydata, void *input)
{
	t_data	*data;

	data = input;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == KEY_ESC)
		free_and_exit(data);
	if (keydata.key == KEY_REITERATE)
		reset_orbits(data);
	if (keydata.key == KEY_RESET)
		reset(data);
	if (keydata.key == MLX_KEY_SPACE)
		toggle_pause(data);
}

void	resize_hook(int32_t width, int32_t height, void *input)
{
	t_data	*data;

	data = input;
	data->new_width = width;
	data->new_height = height;
	data->new_px_count = data->new_width * data->new_height;
	data->resizing = 1;
}
