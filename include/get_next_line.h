/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:40:13 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 16:10:06 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "ft_printf.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>

char	*get_next_line(int fd);
char	*read_file(int fd, char *s);
char	*append_free(char *s1, char *s2);
char	*get_line(char *s);
char	*trim(char *s);
int		got_line(char *s);
void	*ft_calloc(size_t count, size_t size);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#endif
