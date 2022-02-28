/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 06:57:17 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 07:14:55 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_print_er(t_data *data, int err_type)
{
	if (err_type == 1)
	{
		write(2, "Ivalid Map\n", 12);
		free(data->map);
		exit(EXIT_FAILURE);
	}
	if (err_type == 3)
	{
		write(2, "No file\n", 9);
		exit(EXIT_FAILURE);
	}
	if (err_type == 2)
	{
		write(2, "Usage : ./fdf <filename> [ case_size z_size ]\n", 47);
		exit(EXIT_FAILURE);
	}
}

void	check_map(t_data *data)
{
	int		i;
	int		len;
	char	**temp;

	i = 0;
	while (data->lines[i])
	{
		len = 0;
		temp = ft_split(data->lines[i], ' ');
		while (temp[len])
			len++;
		if (len != data->width)
			free_print_er(data, 1);
		i++;
	}
}

void	initial_map_check(t_data *data)
{
	int	i;

	i = 0;
	if (data->map[i] == '\n')
		free_print_er(data, 1);
	while (data->map[i])
	{
		if (data->map[i] == '\n' && data->map[i + 1] == '\n')
			free_print_er(data, 1);
		i++;
	}
}

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == 43 || c == 45)
		return (1);
	else
		return (0);
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
