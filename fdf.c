/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:16:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 06:35:04 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_width(char *line)
{
	char	**temp;
	int		i;

	i = 0;
	temp = ft_split(line, ' ');
	while (temp[i])
		i++;
	return (i);
}

void	read_map(int fd, t_data *data)
{
	data->line = (char *)malloc(1);
	data->line[0] = '\0';
	while (data->line)
	{
		data->line = get_next_line(fd);
		if (data->line)
			data->map = ft_strjoin(data->map, data->line);
		free(data->line);
		data->height++;
	}
}

void	ft_mlx(t_mlx *mlx)
{
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 1920, 1080, "FDF");
	mlx->img = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx_hook(mlx->win_ptr, 2, 0, key_hook, mlx);
	mlx_hook(mlx->win_ptr, 4, 0, mouse_press, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, ft_destroy, mlx);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_mlx	mlx;
	int		fd;

	data.height = -1;
	check_args(ac, av, &data);
	mlx.altitude = 1;
	mlx = ft_reset(mlx);
	fd = open(av[1], O_RDONLY);
	read_map(fd, &data);
	initial_map_check(&data);
	data.lines = ft_split(data.map, '\n');
	data.width = get_width(data.lines[0]);
	check_map(&data);
	data.map_name = av[1];
	data.numbers = get_numbers(data.lines, data.height, data.width);
	data.colors = get_colors(data.lines, data.height, data.width);
	mlx.zoom = get_mult(data, mlx);
	mlx.mlx_ptr = mlx_init();
	ft_mlx(&mlx);
	mlx.data = data;
	projection(data, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
