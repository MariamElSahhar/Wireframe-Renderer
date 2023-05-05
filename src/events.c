/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:16:19 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 16:02:54 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	translation(t_data *data, int keycode)
{
	if (keycode == UP)
		data->y_offset += TRANSLATION;
	else if (keycode == DOWN)
		data->y_offset -= TRANSLATION;
	else if (keycode == RIGHT)
		data->x_offset -= TRANSLATION;
	else if (keycode == LEFT)
		data->x_offset += TRANSLATION;
	fdf(data);
}

void	rotation(t_data *data, int keycode)
{
	if (keycode == ALPHA_DEC)
		data->alpha -= THETA;
	else if (keycode == ALPHA_INC)
		data->alpha += THETA;
	else if (keycode == BETA_DEC)
		data->beta -= THETA;
	else if (keycode == BETA_INC)
		data->beta += THETA;
	else if (keycode == GAMMA_DEC)
		data->gamma -= THETA;
	else if (keycode == GAMMA_INC)
		data->gamma += THETA;
	fdf(data);
}

void	zoom(t_data *data, int keycode)
{
	if (keycode == PLUS && data->d < DIM_H / 2)
		data->d += 1;
	else if (keycode == MINUS && data->d > 0)
		data->d -= 1;
	else if (keycode == HIGHER)
		data->z_scale ++;
	else if (keycode == LOWER)
		data->z_scale --;
	fdf(data);
}

void	view(t_data *data, int keycode)
{
	if (keycode == ISO || keycode == RESET)
	{
		data->alpha = X_ROT;
		data->beta = Y_ROT;
		data->gamma = Z_ROT;
	}
	if (keycode == RESET || keycode == CENTER)
	{
		data->x_offset = X_OFFSET;
		data->y_offset = Y_OFFSET;
	}
	if (keycode == RESET)
	{
		data->d = SCALE;
		data->z_scale = Z_SCALE;
	}
	else if (keycode == TOP)
	{
		data->alpha = 0;
		data->beta = 0;
		data->gamma = 0;
	}
	else if (keycode == MENU)
		data->menu *= -1;
	fdf(data);
}

int	key_down(int keycode, t_data *data)
{
	if (keycode == ESC)
		destroy_fdf(data);
	else if (keycode == DOWN || keycode == LEFT
		|| keycode == UP || keycode == RIGHT)
		translation(data, keycode);
	else if (keycode == ALPHA_INC || keycode == ALPHA_DEC
		|| keycode == BETA_INC || keycode == BETA_DEC
		|| keycode == GAMMA_INC || keycode == GAMMA_DEC)
		rotation(data, keycode);
	else if (keycode == PLUS || keycode == MINUS
		|| keycode == HIGHER || keycode == LOWER)
		zoom(data, keycode);
	else if (keycode == RESET || keycode == ISO
		|| keycode == TOP || keycode == CENTER
		|| keycode == MENU)
		view(data, keycode);
	return (0);
}
