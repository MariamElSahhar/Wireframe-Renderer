/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:23:53 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 16:02:54 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_double_pointer(void **ptr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

int	rows_cols(t_grid *grid, char *filename)
{
	int		fd;
	char	*line;
	char	**split_row;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	split_row = ft_split(line, ' ');
	grid->num_cols = 0;
	while (split_row[grid->num_cols])
		grid->num_cols++;
	free_double_pointer((void **) split_row, grid->num_cols);
	grid->num_rows = 0;
	while (line)
	{
		grid->num_rows++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (grid->num_cols * grid->num_rows);
}

void	init_row(t_grid *grid, char *row, int i)
{
	char	**c;
	int		j;

	j = 0;
	c = ft_split(row, ' ');
	grid->z[i] = (int *)malloc(sizeof(int) * grid->num_cols);
	while (j < grid->num_cols)
	{
		grid->z[i][j] = ft_atoi(c[j]);
		j++;
	}
	j = 0;
	while (c[j])
	{
		free(c[j]);
		j++;
	}
	free(c);
}

void	get_z_range(t_grid *grid)
{
	int	i;
	int	j;
	int	max;
	int	min;

	i = 0;
	max = 0;
	min = 0;
	while (i < grid->num_rows)
	{
		j = 0;
		while (j < grid->num_cols)
		{
			if (grid->z[i][j] > max)
				max = grid->z[i][j];
			else if (grid->z[i][j] < min)
				min = grid->z[i][j];
			j++;
		}
		i++;
	}
	grid->dz = max - min;
}

t_grid	*init_grid(char *filename)
{
	int		fd;
	t_grid	*grid;
	char	*row;
	int		i;

	row = 0;
	grid = (t_grid *)malloc(sizeof(t_grid));
	if (!grid || !rows_cols(grid, filename))
		return (0);
	grid->z = (int **)malloc(sizeof(int *) * grid->num_rows);
	if (!grid->z)
		return (0);
	fd = open(filename, O_RDONLY);
	i = 0;
	while (i < grid->num_rows)
	{
		row = get_next_line(fd);
		init_row(grid, row, i);
		i++;
		free(row);
	}
	close(fd);
	get_z_range(grid);
	return (grid);
}
