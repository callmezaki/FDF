#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <stdlib.h>
# include<unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
#include<math.h>
#include<mlx.h>
# define esc 53
# define plus 69
# define minuse 78
# define left 123
# define right  124
# define up 126
# define down 125
# define left_click 4
# define right_click  5
# define scroll_up 4
# define scroll_down  5
# define key_i  34
# define key_p  35
# define key_o  31
# define key_r  15
# define key_x  7
# define key_c  8
# define true  1
# define false  0

typedef struct s_vars
{
	int x0;
	int x1;
	int y0;
	int y1;
	int n;
	int z0;
	int z1;

} t_vars;

typedef struct s_data
{
	int		height;
	int		width;
	char	*line;
	char	*map;
	char	**lines;
	int		**numbers;
	int 	**colors;
	int		case_size;
	int		z_size;
} t_data;

typedef struct s_mlx
{
	void    *mlx_ptr;
	void    *win_ptr;
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		altitude;
	int		position_x;
	int		position_y;
	int		zoom;
	int		x_rota;
	char	r_type;
	int		iso_validity;
	t_data	data;

} t_mlx;

typedef struct s_math
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err; 
	int e2;
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
int	ft_atoi(const char *str);
int **get_numbers(char **lines, int h, int w);
int	count_nbr(long long nbr);
int convert_hex(char *hex);
int **get_colors(char **lines, int h, int w);
int get_width(char *line);
void check_map(t_data data);
int	key_hook(int key, t_mlx *mlx);
// int	mouse_hook(int keycode, t_mlx *mlx);
t_vars get_mult(t_data data, t_vars vars, int zoom);
void projection(t_data data, t_mlx	*mlx);
void draw_line(t_vars vars, t_mlx mlx, int color, t_data data);
int	ft_zoom_in(int key, t_data data, t_mlx mlx);
t_mlx	ft_reset(t_mlx mlx);
// t_vars ft_rotation(t_vars vars , char rotation_type);


#endif