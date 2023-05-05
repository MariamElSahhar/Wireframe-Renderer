/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:09:58 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 16:02:54 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	destroy_fdf(t_data *data)
{
	free_double_pointer((void **) data->grid->z, data->grid->num_rows);
	free(data->grid);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->mlx);
	exit(1);
}

int	*get_points(t_data *data, int x, int y, char f)
{
	int	*p;

	p = (int *)ft_calloc(sizeof(int), 4);
	if (!p)
		return (0);
	p[0] = rot_x(data, x, y, data->grid->z[y][x]);
	p[1] = rot_y(data, x, y, data->grid->z[y][x]);
	if (f == 'h')
	{
		p[2] = rot_x(data, x + 1, y, data->grid->z[y][x + 1]);
		p[3] = rot_y(data, x + 1, y, data->grid->z[y][x + 1]);
	}
	else if (f == 'v')
	{
		p[2] = rot_x(data, x, y + 1, data->grid->z[y + 1][x]);
		p[3] = rot_y(data, x, y + 1, data->grid->z[y + 1][x]);
	}
	return (p);
}

void	put_grid_lines(t_data *data, int i, int j, int z)
{
	int		*p;
	t_line	*line;

	if (j < data->grid->num_cols - 1)
	{
		p = get_points(data, j, i, 'h');
		if (!p)
			return ;
		line = make_line(p[0], p[1], p[2], p[3]);
		put_line(data, line, z);
		free(p);
		free(line);
	}
	if (i < data->grid->num_rows - 1)
	{
		p = get_points(data, j, i, 'v');
		if (!p)
			return ;
		line = make_line(p[0], p[1], p[2], p[3]);
		put_line(data, line, z);
		free(p);
		free(line);
	}
}

void	put_grid(t_data *data)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	while (i < data->grid->num_rows)
	{
		j = 0;
		while (j < data->grid->num_cols)
		{
			z = data->grid->z[i][j];
			put_grid_lines(data, i, j, z);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

void	fdf(t_data *data)
{
	if (data->img != 0)
		mlx_destroy_image(data->mlx, data->img);
	mlx_clear_window(data->mlx, data->mlx_win);
	data->img = mlx_new_image(data->mlx, DIM_W, DIM_H);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
	put_grid(data);
	put_menu(data);
}
