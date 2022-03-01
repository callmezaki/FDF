/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:16:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 06:00:15 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img_addr + (y * mlx->line_length
			+ x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	check_args(int ac, char **av, t_data *data)
{
	int		i;
	int		j;

	j = 2;
	if (access(av[1], F_OK) == -1)
		free_print_er(NULL, 3);
	if (ac == 2)
		return ;
	else if (ac != 4)
		free_print_er(NULL, 2);
	while (j < 4)
	{
		i = 0;
		while (av[j][i])
		{
			if (!ft_isdigit(av[j][i]))
				free_print_er(NULL, 2);
			i++;
		}
		j++;
	}
	data->case_size = atoi(av[2]);
	data->z_size = atoi(av[3]);
}

void	ft_mlx(t_mlx *mlx)
{
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 1920, 1080, "FDF");
	mlx->img = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	mlx_hook(mlx->win_ptr, 17, 0, ft_destroy, mlx);
	mlx_hook(mlx->win_ptr, 2, 0, close_buton, mlx);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_mlx	mlx;
	int		fd;

	data.height = -1;
	check_args(ac, av, &data);
	fd = open(av[1], O_RDONLY);
	mlx.zoom = 0;
	read_map(fd, &data);
	initial_map_check(&data);
	data.lines = ft_split(data.map, '\n');
	data.width = get_width(data.lines[0]);
	check_map(&data);
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
