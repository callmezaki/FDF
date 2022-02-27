/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:16:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/27 05:52:33 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img_addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_vars	*get_pad(t_vars *vars, t_mlx mlx)
{
	int	x;
	int	y;

	x = cos(1.0472) * (mlx.data.height * mlx.zoom);
	y = sin(0.523599) * (mlx.data.width * mlx.zoom);
	vars->pad_x = 1920 - (x + y);
	vars->pad_x = vars->pad_x / 2;
	vars->pad_x += fmin(x, y) * 0.1;
	x = cos(0.523599) * (mlx.data.width * mlx.zoom);
	y = sin(0.523599) * (mlx.data.height * mlx.zoom);
	vars->pad_y = 1080 - (x + y);
	vars->pad_y = vars->pad_y / 2;
	vars->pad_y += fmax(x, y) / 3;
	return (vars);
}

void	draw_line(t_vars vars, t_mlx mlx, int color, t_data data)
{
	t_math math;

	vars.z0 = data.numbers[vars.y0][vars.x0];
	vars.z1 = data.numbers[vars.y1][vars.x1];
	if (data.z_size != 0 && data.case_size != 0)
	{
		vars.z0 *= data.z_size;
		vars.z1 *= data.z_size;
	}
	if (vars.z0 != 0)
		vars.z0 *= mlx.altitude;
	if (vars.z1 != 0)
		vars.z1 *= mlx.altitude;
	vars.y0 *= mlx.zoom;
	vars.y1 *= mlx.zoom;
	vars.x0 *= mlx.zoom;
	vars.x1 *= mlx.zoom;
	if (mlx.iso_validity == TRUE)
	{
		vars.x0 = (vars.x0 - vars.y0) * cos(0.8);
		vars.y0 = ((vars.x0 + vars.y0) * sin(0.8)) - vars.z0;
		vars.x1 = (vars.x1 - vars.y1) * cos(0.8);
		vars.y1 = ((vars.x1 + vars.y1) * sin(0.8)) - vars.z1;
	}
	vars = ft_rotation(vars, mlx, mlx.r_type);
	vars.x1 += vars.pad_x;
	vars.y1 += vars.pad_y;
	vars.x0 += vars.pad_x;
	vars.y0 += vars.pad_y;
	math.dx = abs(vars.x1 - vars.x0);
	math.sx = vars.x0 < vars.x1 ? 1 : -1;
	math.dy = -abs(vars.y1 - vars.y0);
	math.sy = vars.y0 < vars.y1 ? 1 : -1;
	math.err = math.dx + math.dy;
	while (1)
	{
		if ((vars.x0 + mlx.position_x) > 0 && (vars.x0 + mlx.position_x) < 1920 &&
			(vars.y0 + mlx.position_y) > 0 && (vars.y0 + mlx.position_y) < 1080)
			my_mlx_pixel_put(&mlx, vars.x0 + mlx.position_x, vars.y0 + mlx.position_y, color);
		if (vars.x0 == vars.x1 && vars.y0 == vars.y1)
			break ;
		math.e2 = 2 * math.err;
		if (math.e2 >= math.dy)
		{
			if (vars.x0 == vars.x1)
				break ;
			math.err += math.dy;
			vars.x0 += math.sx;
		}
		if (math.e2 <= math.dx)
		{
			if (vars.y0 == vars.y1)
				break ;
			math.err += math.dx;
			vars.y0 += math.sy;
		}
	}
}

void	ft_strings(t_mlx *mlx, t_vars *vars)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 920, 10, 11520457, "Map name : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1040, 10, 11520457, mlx->data.map_name);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 10, 11520457, "INFO");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 40, 11520457, "ZOOM :");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 100, 40, 11520457, ft_itoa(mlx->zoom));
	if (mlx->zoom == 0)
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 120, 40, 16711680, "You can't zoom out any more!");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 70, 11520457, "X posintion : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 70, 11520457, ft_itoa(vars->pad_x + mlx->position_x));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 100, 11520457, "Y posintion : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 100, 11520457, ft_itoa(vars->pad_y + mlx->position_y));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 130, 11520457, "Altitude : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 130, 11520457, ft_itoa(mlx->altitude));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 800, 11520457, "KEY MAP");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 850, 11520457, "Zoom in : scroll up , zoom out : scroll down      |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 880, 11520457, "Move up : arrow up , move down : arrow down       |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 910, 11520457, "Move right : arrow right , move left : arrow left |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 940, 11520457, "X rotation : + with 'X' , - with 'S'              |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 970, 11520457, "Y rotation : + with 'C' , - with 'D'              |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 1000, 11520457, "Z rotation : + with 'Z' , - with 'A'              |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 1030, 11520457, "Altitude : + with '+' , - with '-'                |");
}

void	projection(t_data data, t_mlx *mlx)
{
	int		x;
	int		y;
	t_vars	*vars;

	y = 0;
	vars = (t_vars *)malloc(sizeof(t_vars));
	vars = get_pad(vars, *mlx);
	while (y < data.height)
	{
		x = 0;
		while (x < data.width)
		{
			if (x < data.width - 1)
			{
				vars->x0 = x;
				vars->x1 = x + 1;
				vars->y0 = y;
				vars->y1 = y;
				draw_line(*vars,*mlx, data.colors[y][x], data);
			}
			if (y < data.height - 1)
			{
				vars->x0 = x;
				vars->x1 = x;
				vars->y0 = y;
				vars->y1 = y + 1;
				draw_line(*vars,*mlx, data.colors[y][x], data);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	ft_strings(mlx, vars);
}

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == 43 || c == 45)
		return (1);
	else
		return (0);
}

void	check_args(int ac , char **av)
{
	int		i;
	int		j;

	j = 2;
	if (access(av[1], F_OK) == -1)
	{
		write(2, "No file\n", 9);
		exit(EXIT_FAILURE);
	}
	if (ac == 2)
		return ;
	else if (ac != 4)
	{
		write(2, "Usage : ./fdf <filename> [ case_size z_size ]\n", 47);
		exit(EXIT_FAILURE);
	}
	while (j < 4)
	{
		i = 0;
		while (av[j][i])
		{
			if (!ft_isdigit(av[j][i]))
			{
				write(2, "Usage : ./fdf <filename> [ case_size z_size ]\n", 47);
				exit(EXIT_FAILURE);
			}
			i++;
		}
		j++;
	}
}

int	main (int ac, char **av)
{
	t_data	data;
	t_mlx	mlx;
	int fd;

	check_args (ac, av);
	if (ac == 4)
	{
		data.case_size = atoi(av[2]);
		data.z_size = atoi(av[3]);
	}
	data.height = -1;
	mlx.altitude = 1;
	fd = open(av[1], O_RDONLY);
	data.line = (char *)malloc(1);
	data.line[0] = '\0';
	mlx = ft_reset(mlx);
	while (data.line)
	{
		data.line = get_next_line(fd);
		if (data.line)
			data.map = ft_strjoin(data.map, data.line);
		free(data.line);
		data.height++;
	}
	data.lines = ft_split(data.map, '\n');
	data.width = get_width(data.lines[0]);
	data.map_name = av[1];
	check_map(data);
	data.numbers = get_numbers(data.lines, data.height, data.width);
	data.colors = get_colors(data.lines, data.height, data.width);
	mlx.mlx_ptr = mlx_init();
	mlx.zoom = get_mult(data, mlx);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 1920, 1080, "FDF");
	mlx.img = mlx_new_image(mlx.mlx_ptr, 1920, 1080);
	mlx.img_addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	mlx.data = data;
	projection(data, &mlx);
	mlx_do_key_autorepeaton(mlx.mlx_ptr);
	mlx_hook(mlx.win_ptr, 2, 0, key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 4, 0, mouse_press, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, ft_destroy, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
