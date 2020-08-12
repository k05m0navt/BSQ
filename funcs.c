#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ft_bsq.h"

int     rows;
int     cols;
char    symb[3];

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

int		ft_atoi(char *str)
{
	int		start;
	int		i;
	int		res;
	int		negative;

	if (!str || !*str)
		return (0);
	start = 0;
	while (str[start] != '\0' && (str[start] == ' ' || str[start] == '\t' ||
			str[start] == '\r' || str[start] == '\n'))
		start++;
	i = start;
	res = 0;
	negative = 0;
	while (str[i] != '\0' && ((str[i] >= '0' && str[i] <= '9') ||
				(i == start && (str[i] == '-' || str[i] == '+'))))
	{
		if (str[i] == '-')
			negative = 1;
		if (str[i] >= '0' && str[i] <= '9')
			res = (res * 10) + (str[i] - 48);
		++i;
	}
	return ((negative) ? res * -1 : res);
}

int     ft_min(int a, int b, int c) 
{ 
    int     m;

    m = a;
    if (m > b)  
        m = b;
    if (m > c)  
        m = c;
    return (m);
}

char    **ft_parse_map(char const *file_name)
{
    int		fd;
    int     row;
    int     col;
	char	buf[1];
    int     counter;
    char     **map;

    if (file_name)
        fd = open(file_name, O_RDONLY);
    else
        fd = 0;
    if (fd == -1)
        return (NULL);
    map = NULL;
    counter = 0;
    while (counter < 5)
    {
        read(fd, buf, sizeof(buf));
        if (counter == 0)
            rows = ft_atoi(buf);
        else if (counter == 1 || counter == 2 || counter == 3)
            symb[counter-1] = buf[0];
        counter++;
    }
    row = 0;
    col = 0;
    cols = 0;
    while (read(fd, buf, sizeof(buf)))
    {
        if (buf[0] != '\n')
        {
            if (buf[0] != symb[0] && buf[0] != symb[1])
                return (NULL);
            col++;
        }
        else
        {
            if (cols != col && row != 0)
                return (NULL);
            cols = col;
            row++;
            col = 0;
        }
    }
    close(fd);
    fd = open(file_name, O_RDONLY);
    read(fd, buf, sizeof(buf));
    read(fd, buf, sizeof(buf));
    read(fd, buf, sizeof(buf));
    read(fd, buf, sizeof(buf));
    read(fd, buf, sizeof(buf));
    row = 0;
    col = 0;
    map = (char**)malloc(rows * sizeof(char*));
    while (row < rows)
    {
        map[row] = (char*)malloc(cols * sizeof(char));
        row++;
    }
    row = 0;
    col = 0;
    while (read(fd, buf, sizeof(buf)))
    {
        if (buf[0] != '\n')
        {
            map[row][col] = buf[0];
            col++;
        }
        else
        {
            cols = col;
            row++;
            col = 0;
        }
    }
    return (map);
}

char    **ft_find_square(char **map)
{
    int     **M;
    int     **S;
    int     i;
    int     j;
    int     s_max;
    int     r_max;
    int     c_max;
    int     row;

    i = 0;
    j = 0;
    row = 0;
    M = (int**)malloc(rows * sizeof(int*));
    S = (int**)malloc(rows * sizeof(int*));
    while (row < rows)
    {
        M[row] = (int*)malloc(cols * sizeof(int));
        S[row] = (int*)malloc(cols * sizeof(int));
        row++;
    }
    if (map != NULL)
    {
        while (i < rows)
        {
            j = 0;
            while (j < cols)
            {
                if (map[i][j] == symb[0])
                    M[i][j] = 1;
                else if (map[i][j] == symb[1])
                    M[i][j] = 0;
                j++;
            }
            i++;
        }
        i = 0;
        j = 0;
        while (i < rows)
        {
            S[i][0] = M[i][0];
            i++;
        }
        while (j < cols)
        {
            S[0][j] = M[0][j];
            j++;
        }
        i = 1;
        j = 1;
        while (i < rows)
        {
            j = 1;
            while (j < cols)
            {
                if(M[i][j] == 1)  
                    S[i][j] = ft_min(S[i][j-1], S[i-1][j], S[i-1][j-1]) + 1; 
                else
                    S[i][j] = 0;
                j++;
            }
            i++;
        }
        s_max = S[0][0];
        r_max = 0;
        c_max = 0;
        i = 0;
        j = 0;
        while (i < rows)
        {
            j = 0;
            while (j < cols)
            {
                if (s_max < S[i][j])
                {
                    s_max = S[i][j];
                    r_max = i;
                    c_max = j;
                }
                j++;
            }
            i++;
        }
        i = r_max;
        j = c_max;
        while (i > r_max - s_max)
        {
            j = c_max;
            while (j > c_max - s_max)
            {
                map[i][j] = symb[2];
                j--;
            }
            i--;
        }
        return (map);
    }
    else
        return (NULL);
}

void    ft_print_map(char **map)
{
    int     i;
    int     j;

    if (map == NULL)
    {
        ft_putstr("map error\n");
        return ;
    }
    i = 0;
    j = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            ft_putchar(map[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}