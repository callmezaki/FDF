/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 05:40:09 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 07:19:31 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# include <stdio.h>
# include <stdlib.h>
# include<unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>
# define ESC 53

typedef struct s_vars
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;
	int	z0;
	int	z1;
	int	pad_x;
	int	pad_y;

}	t_vars;

typedef struct s_data
{
	int		height;
	int		width;
	char	*line;
	char	*map;
	char	**lines;
	int		**numbers;
	int		**colors;
	int		case_size;
	int		z_size;
}	t_data;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		zoom;
	t_data	data;
}	t_mlx;

typedef struct s_math
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
}	t_math;

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *src);
int		ft_atoi(const char *str);
int		**get_numbers(char **lines, int h, int w);
int		count_nbr(long long nbr);
int		convert_hex(char *hex);
int		**get_colors(char **lines, int h, int w);
int		get_width(char *line);
void	check_map(t_data *data);
int		close_buton(int key, void *vars);
int		get_mult(t_data data, t_mlx mlx);
void	projection(t_data data, t_mlx *mlx);
void	two_lines_draw(int x, int y, t_vars *vars, t_mlx *mlx);
void	draw_line(t_vars *vars, t_mlx mlx, int color, t_data data);
void	ft_iso(t_vars *vars);
t_mlx	ft_reset(t_mlx mlx);
void	initial_map_check(t_data *data);
void	free_print_er(t_data *data, int err_type);
int		ft_isdigit(int c);
void	get_pad(t_vars *vars, t_mlx mlx);
void	padding(t_vars *vars);
void	bresenham(t_vars *vars, t_mlx mlx, t_math math, int color);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	read_map(int fd, t_data *data);
int		ft_destroy(t_mlx *mlx);
void	handle_zoom_center(t_vars *vars, t_mlx mlx, t_data data);
int		count_nbr(long long nbr);
int		convert_hex(char *hex);

#endif