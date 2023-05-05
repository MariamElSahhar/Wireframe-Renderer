/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:49:12 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 16:02:54 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	zoom_center(t_data *data, int *x, int *y)
{
	*y *= data->d;
	*x *= data->d;
	*y -= (data->grid->num_rows * data->d / 2);
	*x -= (data->grid->num_cols * data->d / 2);
}

int	rot_x(t_data *data, int x, int y, int z)
{
	float	rot_x;

	zoom_center(data, &x, &y);
	z *= data->z_scale;
	rot_x = x * cos(data->beta) * cos(data->gamma)
		+ y * (cos(data->alpha) * sin(data->gamma) * sin(data->beta)
			- cos(data->gamma) * sin(data->alpha))
		+ z * (sin(data->alpha) * sin(data->gamma)
			+ cos(data->alpha) * cos(data->gamma) * sin(data->beta));
	return (rot_x + data->x_offset);
}

int	rot_y(t_data *data, int x, int y, int z)
{
	float	rot_y;

	z *= data->z_scale;
	zoom_center(data, &x, &y);
	rot_y = x * cos(data->beta) * sin(data->gamma)
		+ y * (cos(data->alpha) * cos(data->gamma)
			+ sin(data->alpha) * sin(data->beta) * sin(data->gamma))
		+ z * (0 - cos(data->gamma) * sin(data->alpha)
			+ cos(data->alpha) * sin(data->beta) * sin(data->gamma));
	return (rot_y + data->y_offset);
}

void	put_menu(t_data *data)
{
	if (data->menu > 0)
	{
		mlx_string_put(data->mlx, data->mlx_win, 2, 0, WHITE, "Commands:");
		mlx_string_put(data->mlx, data->mlx_win, 2, 15, WHITE,
			"Arrow keys to pan");
		mlx_string_put(data->mlx, data->mlx_win, 2, 30, WHITE,
			"Q,W,E,A,S,D to rotate");
		mlx_string_put(data->mlx, data->mlx_win, 2, 45, WHITE, "+,- to zoom");
		mlx_string_put(data->mlx, data->mlx_win, 2, 60, WHITE,
			"<,> to toggle altitude scale");
		mlx_string_put(data->mlx, data->mlx_win, 2, 75, WHITE, "C to center");
		mlx_string_put(data->mlx, data->mlx_win, 2, 90, WHITE,
			"T for top view");
		mlx_string_put(data->mlx, data->mlx_win, 2, 105, WHITE,
			"I for isometric view");
		mlx_string_put(data->mlx, data->mlx_win, 2, 120, WHITE,
			"H to toggle menu");
		mlx_string_put(data->mlx, data->mlx_win, 2, 135, WHITE,
			"SPACE to reset image");
	}
}
