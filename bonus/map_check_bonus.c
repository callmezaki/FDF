/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 20:35:35 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 07:59:46 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
		ft_free_double((void **)temp);
		if (len < data->width)
			free_print_er(data, 1);
		i++;
	}
}

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

void	initial_map_check(t_data *data)
{
	int	i;

	i = 0;
	if (!data->map)
		free_print_er(data, 1);
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
	data->case_size = ft_atoi(av[2]);
	data->z_size = ft_atoi(av[3]);
}
