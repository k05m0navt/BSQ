/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cillaoi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 19:30:32 by cillaoi           #+#    #+#             */
/*   Updated: 2020/08/12 19:30:37 by cillaoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BSQ_H
# define FT_BSQ_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_atoi(char *str);
int		ft_min(int a, int b, int c);
char	**ft_parse_map(char const *file_name);
char	**ft_find_square(char **map);
void	ft_print_map(char **map);
int		ft_before_n(int fd);
char	**ft_push_to_map(char **map, int g_rows, int row, int col, int g_cols, int fd, char g_buf[1]);

#endif
