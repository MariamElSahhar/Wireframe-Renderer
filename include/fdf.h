/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:28:15 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 16:03:12 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdint.h>

# define WHITE 0xffffff
# define LEVEL_E 0x4B0082
# define LEVEL_D 0x8B008B
# define LEVEL_C 0xDCCDE8
# define LEVEL_B 0xD99AC5
# define LEVEL_A 0xB37BA4

# define DIM_W 1000
# define DIM_H 1000
# define X_OFFSET DIM_W/2
# define Y_OFFSET DIM_H/2
# define X_ROT 45 * (M_PI / 180)
# define Y_ROT -35.264 * (M_PI / 180)
# define Z_ROT 30 * (M_PI / 180)
# define SCALE 12
# define Z_SCALE 3
# define TRANSLATION 10
# define THETA 0.075

typedef struct s_grid
{
	int	num_rows;
	int	num_cols;
	int	**z;
	int	dz;
}	t_grid;

typedef struct s_line
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		color;
}	t_line;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	t_grid	*grid;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		num_lines;
	int		x_offset;
	int		y_offset;
	float	alpha;
	float	beta;
	float	gamma;
	int		distance;
	int		d;
	int		z_scale;
	int		menu;
}	t_data;

typedef enum e_keycodes
{
	ESC = 53,
	LEFT = 123,
	RIGHT = 124,
	DOWN = 125,
	UP = 126,
	ALPHA_INC = 13,
	ALPHA_DEC = 1,
	BETA_INC = 2,
	BETA_DEC = 0,
	GAMMA_INC = 14,
	GAMMA_DEC = 12,
	TOP = 17,
	ISO = 34,
	PLUS = 24,
	MINUS = 27,
	DESTROY = 17,
	RESET = 49,
	CENTER = 8,
	MENU = 4,
	HIGHER = 47,
	LOWER = 43,
}	t_keycodes;

void	fdf(t_data *data);
int		init_data(t_data *data, char *filename);
t_grid	*make_grid(t_data *data, char *filename);
t_grid	*init_grid(char *filename);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
t_grid	*init_grid(char *filename);
int		key_down(int keycode, t_data *data);
void	rotation(t_data *data, int keycode);
int		destroy_fdf(t_data *data);
t_line	*make_line(int x0, int y0, int x1, int y1);
void	put_line(t_data *data, t_line *line, int z);
int		rot_x(t_data *data, int x, int y, int z);
int		rot_y(t_data *data, int x, int y, int z);
void	free_double_pointer(void **ptr, int size);
void	put_menu(t_data *data);

#endif
