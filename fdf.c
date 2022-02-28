/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:16:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 03:05:05 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_pad(t_vars *vars, t_mlx mlx)
{
	int	x;
	int	y;

	x = cos(1.0472) * (mlx.data.height * mlx.zoom);
	y = sin(0.523599) * (mlx.data.width * mlx.zoom);
	vars->pad_x = 1920 - (x + y);
	vars->pad_x = vars->pad_x / 2;
	vars->pad_x += fmin(x, y) * 1.2;
	x = cos(0.523599) * (mlx.data.width * mlx.zoom);
	y = sin(0.523599) * (mlx.data.height * mlx.zoom);
	vars->pad_y = 1080 - (x + y);
	vars->pad_y = vars->pad_y / 2;
	vars->pad_y += fmax(x, y) * 0.8;
}

int	main(int ac, char **av)
{
	t_data	data;
	t_mlx	mlx;
	int		fd;

	check_args(ac, av);
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
	initial_map_check(&data);
	data.lines = ft_split(data.map, '\n');
	data.width = get_width(data.lines[0]);
	data.map_name = av[1];
	check_map(&data);
	data.numbers = get_numbers(data.lines, data.height, data.width);
	data.colors = get_colors(data.lines, data.height, data.width);
	mlx.mlx_ptr = mlx_init();
	mlx.zoom = get_mult(data, mlx);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 1920, 1080, "FDF");
	mlx.img = mlx_new_image(mlx.mlx_ptr, 1920, 1080);
	mlx.img_addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
			&mlx.line_length, &mlx.endian);
	mlx.data = data;
	projection(data, &mlx);
	mlx_do_key_autorepeaton(mlx.mlx_ptr);
	mlx_hook(mlx.win_ptr, 2, 0, key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 4, 0, mouse_press, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, ft_destroy, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
