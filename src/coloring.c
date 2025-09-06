/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:48:52 by ssuopea           #+#    #+#             */
/*   Updated: 2025/09/06 16:14:55 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int32_t	get_pixel_color(uint8_t *pixels, int i)
{
	pixels += i * 4;
	return ((pixels[0] << 24)
		+ (pixels[1] << 16)
		+ (pixels[2] << 8)
		+ pixels[3]);
}

void	clear_screen(t_data *data)
{
	ft_memset(data->frame->pixels, 0, data->px_count * sizeof(int32_t));
}

void	color_pixels(t_data *data)
{
	int	i;
	int	color;

	i = 0;
	while (i < data->px_count)
	{
		if (!data->escape_times[i])
			mlx_put_pixel(data->frame, x(i, data), y(i, data), 0xFF);
		else
		{
			color = (((data->iteration - data->escape_times[i] + 30) % 0x88)
					* 0x020202) << 8 | 0xFF;
			mlx_put_pixel(data->frame, x(i, data), y(i, data), color);
		}
		i++;
	}
}
