#ifndef FT_BSQ_H
# define FT_BSQ_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_atoi(char *str);
int     ft_min(int a, int b, int c);
char    **ft_parse_map(char const *file_name);
char    **ft_find_square(char **map);
void    ft_print_map(char **map);

#endif