/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cillaoi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 19:31:55 by cillaoi           #+#    #+#             */
/*   Updated: 2020/08/12 19:31:58 by cillaoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ft_bsq.h"

int		g_rows;
int		g_cols;
char	g_symb[3];
char	g_buf[1];
int		**g_m;
int		**g_s;
int		g_s_max;
int		g_r_max;
int		g_c_max;
int		g_first_line_length;

void	ft_parse_symb(int fd)
{
	int		counter;

	g_rows = 0;
	counter = 0;
	while (counter < g_first_line_length)
	{
		read(fd, g_buf, sizeof(g_buf));
		if (counter < g_first_line_length - 4)
			g_rows = g_rows * 10 + ft_atoi(g_buf);
		else
			g_symb[counter - 1] = g_buf[0];
		counter++;
	}
}

int		ft_check_map(int fd)
{
	int		row;
	int		col;

	row = 0;
	col = 0;
	g_cols = 0;
	while (read(fd, g_buf, sizeof(g_buf)))
	{
		if (g_buf[0] != '\n')
		{
			if (g_buf[0] != g_symb[0] && g_buf[0] != g_symb[1])
				return (0);
			col++;
		}
		else
		{
			if (g_cols != col && row != 0)
				return (0);
			g_cols = col;
			row++;
			col = 0;
		}
	}
	return (1);
}

char	**ft_parse_map(char const *file_name)
{
	int		fd;
	int		row;
	int		col;
	int		counter;
	char	**map;

	if (file_name)
		fd = open(file_name, O_RDONLY);
	else
		fd = 0;
	if (fd == -1)
		return (NULL);
	map = NULL;
	g_first_line_length = ft_before_n(fd);
	close(fd);
	fd = open(file_name, O_RDONLY);
	ft_parse_symb(fd);
	row = 0;
	col = 0;
	g_cols = 0;
	if (ft_check_map(fd) == 0)
		return (NULL);
	close(fd);
	fd = open(file_name, O_RDONLY);
	counter = 0;
	while (counter++ < 5)
		read(fd, g_buf, sizeof(g_buf));
	row = 0;
	col = 0;
	map = (char**)malloc(g_rows * sizeof(char*));
	while (row < g_rows)
	{
		map[row] = (char*)malloc(g_cols * sizeof(char));
		row++;
	}
	row = 0;
	col = 0;
	while (read(fd, g_buf, sizeof(g_buf)))
	{
		if (g_buf[0] != '\n')
		{
			map[row][col] = g_buf[0];
			col++;
		}
		else
		{
			g_cols = col;
			row++;
			col = 0;
		}
	}
	ft_putchar(map[1][1]);
	ft_putchar('\n');
	return (map);
}

char	**ft_find_square(char **map)
{
	int		i;
	int		j;
	int		row;

	i = 0;
	j = 0;
	row = 0;
	g_m = (int**)malloc(g_rows * sizeof(int*));
	g_s = (int**)malloc(g_rows * sizeof(int*));
	while (row < g_rows)
	{
		g_m[row] = (int*)malloc(g_cols * sizeof(int));
		g_s[row] = (int*)malloc(g_cols * sizeof(int));
		row++;
	}
	if (map != NULL)
	{
		while (i < g_rows)
		{
			j = 0;
			while (j < g_cols)
			{
				if (map[i][j] == g_symb[0])
					g_m[i][j] = 1;
				else if (map[i][j] == g_symb[1])
					g_m[i][j] = 0;
				j++;
			}
			i++;
		}
		i = 0;
		j = 0;
		while (i < g_rows)
		{
			g_s[i][0] = g_m[i][0];
			i++;
		}
		while (j < g_cols)
		{
			g_s[0][j] = g_m[0][j];
			j++;
		}
		i = 1;
		j = 1;
		while (i < g_rows)
		{
			j = 1;
			while (j < g_cols)
			{
				if (g_m[i][j] == 1)
					g_s[i][j] = ft_min(g_s[i][j - 1],
									g_s[i - 1][j], g_s[i - 1][j - 1]) + 1;
				else
					g_s[i][j] = 0;
				j++;
			}
			i++;
		}
		g_s_max = g_s[0][0];
		g_r_max = 0;
		g_c_max = 0;
		i = 0;
		j = 0;
		while (i < g_rows)
		{
			j = 0;
			while (j < g_cols)
			{
				if (g_s_max < g_s[i][j])
				{
					g_s_max = g_s[i][j];
					g_r_max = i;
					g_c_max = j;
				}
				j++;
			}
			i++;
		}
		i = g_r_max;
		j = g_c_max;
		while (i > g_r_max - g_s_max)
		{
			j = g_c_max;
			while (j > g_c_max - g_s_max)
			{
				map[i][j] = g_symb[2];
				j--;
			}
			i--;
		}
		return (map);
	}
	else
		return (NULL);
}

void	ft_print_map(char **map)
{
	int		i;
	int		j;

	if (map == NULL)
	{
		ft_putstr("map error\n");
		return ;
	}
	i = 0;
	j = 0;
	while (i < g_rows)
	{
		j = 0;
		while (j < g_cols)
		{
			ft_putchar(map[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
