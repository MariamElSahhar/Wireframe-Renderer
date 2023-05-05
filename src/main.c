/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:30:57 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 16:02:54 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_grid	*make_grid(t_data *data, char *filename)
{
	t_grid	*grid;

	grid = init_grid(filename);
	if (!grid)
		return (0);
	data->grid = grid;
	data->num_lines = ((grid->num_cols - 1) * grid->num_rows)
		* ((grid->num_rows - 1) * grid->num_cols);
	return (grid);
}

int	init_data(t_data *data, char *filename)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->img = mlx_new_image(data->mlx, DIM_W, DIM_H);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
	data->mlx_win = mlx_new_window(data->mlx, DIM_W, DIM_H, filename);
	data->grid = make_grid(data, filename);
	data->alpha = X_ROT;
	data->beta = Y_ROT;
	data->gamma = Z_ROT;
	data->d = ((DIM_W) / (data->grid->num_rows * 3));
	if (data->d == 0)
		data->d = 1;
	data->z_scale = Z_SCALE;
	data->menu = 1;
	data->x_offset += ((DIM_W + data->x_offset) / 2);
	data->y_offset += ((DIM_H + data->y_offset) / 2);
	if (!data->mlx_win || !data->grid)
	{
		free(data->mlx_win);
		free(data->mlx);
		return (0);
	}
	return (1);
}

int	check_input(int c, char **v)
{
	char	*p;
	int		fd;

	if (c != 2)
	{
		ft_printf("Error: Please enter a valid file name\n");
		return (0);
	}
	p = ft_strrchr(v[1], '.');
	if (!p || ft_strncmp(p, ".fdf", ft_strlen(p)) != 0)
	{
		ft_printf("Error: File must have .fdf extension\n");
		return (0);
	}
	fd = open(v[1], O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		ft_printf("Error: Invalid file\n");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	main(int c, char **v)
{
	t_data	data;

	if (!check_input(c, v))
		return (-1);
	if (!init_data(&data, v[1]))
		return (-1);
	fdf(&data);
	mlx_hook(data.mlx_win, 2, 1L << 0, &key_down, &data);
	mlx_hook(data.mlx_win, 17, 0, &destroy_fdf, &data);
	mlx_loop(data.mlx);
	free(data.mlx);
	free(data.mlx_win);
	return (0);
}
