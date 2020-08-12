/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cillaoi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 22:09:52 by cillaoi           #+#    #+#             */
/*   Updated: 2020/08/12 22:09:57 by cillaoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ft_bsq.h"

char	**ft_push_to_map(char **map, int g_rows, int row, int col, int g_cols, int fd, char *g_buf)
{
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
			ft_putchar(g_buf[0]);
			map[row][col] = g_buf[0];
			col++;
		}
		else
		{
			ft_putchar('\n');
			row++;
			col = 0;
		}
	}
	return (map);
}
