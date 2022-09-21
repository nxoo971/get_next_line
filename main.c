#include "get_next_line.h"
#include <stdio.h>
int		main(int ac, char **av)
{
	(void)ac;
	char	*res;
	int		fd = open(av[1], O_RDONLY);
	//int		fd2 = open(av[2], O_RDONLY);

	while ((res = get_next_line(fd)))
		printf("%s", res);
	printf("%s", res);
	// res = get_next_line(fd);
	// printf("1: %s", res);
	// res = get_next_line(fd2);
	// printf("2: %s", res);
	// res = get_next_line(fd);
	// printf("3: %s", res);
	// res = get_next_line(fd2);
	// printf("4: %s", res);
	// res = get_next_line(fd);
	// printf("5: %s", res);
	// res = get_next_line(fd2);
	// printf("6: %s", res);
	// res = get_next_line(fd);
	// printf("7: %s", res);
	// res = get_next_line(fd2);
	// printf("8: %s", res);

	// res = get_next_line(fd);
	// printf("9: %s", res);
	// res = get_next_line(fd2);
	// printf("10: %s", res);
	// res = get_next_line(fd);
	// printf("11: %s", res);
	// res = get_next_line(fd2);
	// printf("12: %s", res);

	close(fd);
	//close(fd2);
	return (0);
}
