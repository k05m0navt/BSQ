#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ft_bsq.h"

int     main(int argc, char *argv[])
{
    int     counter;

	counter = 0;
	if (argc > 1)
		while (++counter < argc)
		{
			ft_print_map(ft_find_square(ft_parse_map(argv[counter])));
			if (counter < argc - 1)
				ft_putchar('\n');
		}
	else
		ft_print_map(ft_find_square(ft_parse_map(0)));
	return (0);
}