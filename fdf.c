/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:16:52 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/26 06:05:56 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include<mlx.h>
#include "fdf.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img_addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



void draw_line(t_vars vars, t_mlx mlx, int color, t_data data)
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
	vars = get_mult(data ,vars, mlx.zoom);
	// printf("\n%d\n",mlx.iso_validity);
	if (mlx.iso_validity == true)
	{
		vars.x0 = (vars.x0 - vars.y0) * cos(0.8);
		vars.y0 = ((vars.x0 + vars.y0) * sin(0.8)) - vars.z0;
		vars.x1 = (vars.x1 - vars.y1) * cos(0.8);
		vars.y1 = ((vars.x1 + vars.y1) * sin(0.8)) - vars.z1;
	}
	math.dx = abs(vars.x1 - vars.x0);
	math.sx = vars.x0 < vars.x1 ? 1 : -1;
	math.dy = -abs(vars.y1 -vars.y0);
	math.sy = vars.y0 < vars.y1 ? 1 : -1;
	math.err = math.dx + math.dy;
	while(1)
	{
		if((vars.x0 + 800 + mlx.position_x) > 0 && (vars.x0 + 800 + mlx.position_x) < 1920 &&
		 (vars.y0 + 300 + mlx.position_y) > 0 && (vars.y0 + 300 + mlx.position_y) < 1080)
			my_mlx_pixel_put(&mlx, vars.x0 + 800 + mlx.position_x, vars.y0 + 300 + mlx.position_y,color);
		if(vars.x0 == vars.x1 && vars.y0 == vars.y1)
			break; 
		math.e2 = 2*math.err;
		if(math.e2 >= math.dy)
		{
			if(vars.x0 == vars.x1)
				break;
			math.err += math.dy;
			vars.x0 += math.sx; 
		}
		if(math.e2 <= math.dx)
		{
			if(vars.y0 == vars.y1)
				break;
			math.err += math.dx;
			vars.y0 += math.sy;
		}
	}
}

void projection(t_data data, t_mlx *mlx)
{
	int x =0;
	int y = 0;
	t_vars	vars;

	while(y < data.height )
	{
		x = 0;
		while(x < data.width )
		{
			if(x < data.width - 1)
			{
				vars.x0 = x;
				vars.x1 = x + 1;
				vars.y0 = y;
				vars.y1 = y;
				draw_line(vars,*mlx, data.colors[y][x], data);
			}
			if(y < data.height - 1)
			{
				vars.x0 = x;
				vars.x1 = x;
				vars.y0 = y;
				vars.y1 = y + 1;
				draw_line(vars,*mlx, data.colors[y][x], data);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}
int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57 )|| c == 43 || c == 45)
		return (1);
	else
		return (0);
}

void check_args (int ac , char **av)
{
	int i = 0;
	int j = 2;

	if (ac  == 2)
		return ;
	else if (ac != 4)
	{
		write(2, "Usage : ./fdf <filename> [ case_size z_size ]\n",47);
		exit(EXIT_FAILURE);
	}
	while(j < 4)
	{
		i = 0;
		while(av[j][i])
		{
			if(!ft_isdigit(av[j][i]))
			{
				write(2, "Usage : ./fdf <filename> [ case_size z_size ]\n",47);
				exit(EXIT_FAILURE);
			}
			i++;
		}
		j++;
	}
}

int main (int ac, char **av)
{
	t_data	data;
	t_mlx mlx;
	(void)ac;
	
	check_args (ac, av);
	if (ac == 4)
	{
		data.case_size = atoi(av[2]);
		data.z_size = atoi(av[3]);
	}
	data.height = -1;
	mlx.altitude = 1;
	mlx.zoom	= 0;
	mlx.position_x	= 0;
	mlx.position_y	= 0;
	mlx.r_type = 'n';
	mlx.iso_validity = 1;
	int fd = open(av[1], O_RDWR);
	data.line = (char *)malloc(1);
	data.line[0] = '\0';
	mlx = ft_reset(mlx);
	while(data.line)
	{
		data.line = get_next_line(fd);
		if (data.line)
			data.map = ft_strjoin(data.map, data.line);
		free(data.line);
		data.height++;
	}
	data.lines = ft_split(data.map, '\n');
	data.width = get_width(data.lines[0]);
	check_map(data);
	mlx.mlx_ptr = mlx_init();
	data.numbers = get_numbers(data.lines, data.height, data.width);
	data.colors = get_colors(data.lines, data.height, data.width);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 1920, 1080, "FDF");
	mlx.img = mlx_new_image(mlx.mlx_ptr, 1920, 1080);
	mlx.img_addr = mlx_get_data_addr(mlx.img,  &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	mlx.data = data;
	projection(data, &mlx);
	mlx_do_key_autorepeaton(mlx.mlx_ptr);
	mlx_hook(mlx.win_ptr, 2, 0, key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);	

	return(0);
}