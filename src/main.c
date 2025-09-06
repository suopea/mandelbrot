/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:52:50 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 16:17:23 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	loop_hook(void *input);
static int	initialize(t_data *data, char **argv);

int	main(int argc, char **argv)
{
	t_data	data;

	validate_inputs(argc, argv);
	if (!ft_strcmp(argv[1], "julia"))
		data.type = julia;
	else
		data.type = mandelbrot;
	initialize(&data, argv);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_everything(&data);
	return (0);
}

static int	initialize(t_data *data, char **argv)
{
	initialize_program(data);
	if (!initialize_mlx(data))
		free_and_exit(data);
	if (data->type == julia)
	{
		data->c.i = ft_strtod(argv[2], NULL);
		data->c.r = ft_strtod(argv[3], NULL);
	}
	mlx_mouse_hook(data->mlx, mouse_hook, data);
	mlx_scroll_hook(data->mlx, scroll_hook, data);
	mlx_resize_hook(data->mlx, resize_hook, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_key_hook(data->mlx, key_hook, data);
	reset(data);
	return (1);
}

static void	loop_hook(void *input)
{
	t_data	*data;

	data = input;
	if (data->paused)
		return ;
	if (about_to_resize(data))
		return ;
	iterate_once(data);
	color_pixels(data);
	if (data->waiting_to_zoom)
	{
		if (data->waiting_to_zoom < ZOOM_WAIT)
		{
			draw_zoom_box(data);
			data->waiting_to_zoom++;
		}
		else
		{
			get_cursor_location_and_zoom(data, data->to_zoom_soon);
			data->to_zoom_soon = 1;
		}
	}
	draw_cursor_cross(data);
}
