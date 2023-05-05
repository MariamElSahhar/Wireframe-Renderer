/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:12:07 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 16:02:54 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= DIM_W || x < 0 || y >= DIM_H || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_line	*make_line(int x0, int y0, int x1, int y1)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->x0 = x0;
	line->y0 = y0;
	line->x1 = x1;
	line->y1 = y1;
	return (line);
}

int	get_color(double dz, int z)
{
	if (abs(z) > dz * .8)
		return (LEVEL_A);
	else if (abs(z) > dz * .6)
		return (LEVEL_B);
	else if (abs(z) > dz * .4)
		return (LEVEL_C);
	else if (abs(z) > dz * .2)
		return (LEVEL_D);
	else
		return (LEVEL_E);
}

void	put_line(t_data *data, t_line *line, int z)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;

	dx = abs(line->x1 - line->x0);
	dy = abs(line->y1 - line->y0);
	err = dx - dy;
	line->color = get_color(data->grid->dz, z);
	while (line->x0 != line->x1 || line->y0 != line->y1)
	{
		put_pixel(data, line->x0, line->y0, line->color);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			line->x0 += (line->x1 - line-> x0) / abs(line->x1 - line->x0) * 1;
		}
		if (e2 < dx)
		{
			err += dx;
			line->y0 += (line->y1 - line->y0) / abs(line->y1 - line->y0) * 1;
		}
	}
	put_pixel(data, line->x0, line->y0, line->color);
}
