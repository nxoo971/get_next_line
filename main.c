#include "get_next_line.h"
#include <stdio.h>
int		main(int ac, char **av)
{
	(void)ac;
	char	*res;
	int		fd = open(av[1], O_RDONLY);
	int		fd2 = open(av[2], O_RDONLY);
	int		fd3 = open(av[2], O_RDONLY);

	// while ((res = get_next_line(fd)))
	// {
	// 	printf("%s", res);
	// 	free(res);
	// }
	//printf("%s", res);
	res = get_next_line(1000);
	printf("1: %s", res);
	if (res)
		free(res);
	res = get_next_line(fd);
	printf("2: %s", res);
	if (res)
		free(res);
	res = get_next_line(1001);
	printf("3: %s", res);
	if (res)
		free(res);
	res = get_next_line(fd2);
	printf("4: %s", res);
	if (res)
		free(res);
	res = get_next_line(1002);
	printf("5: %s", res);
	if (res)
		free(res);
	res = get_next_line(fd3);
	printf("6: %s", res);
	if (res)
		free(res);
	res = get_next_line(1003);
	printf("7: %s", res);
	if (res)
		free(res);
	res = get_next_line(fd);
	printf("8: %s", res);
	if (res)
		free(res);
	res = get_next_line(1004);
	printf("9: %s", res);
	if (res)
		free(res);
	res = get_next_line(fd2);
	printf("10: %s", res);
	if (res)
		free(res);
	res = get_next_line(1005);
	printf("11: %s", res);
	if (res)
		free(res);
	res = get_next_line(fd3);
	printf("12: %s", res);
	if (res)
		free(res);
	res = get_next_line(fd);
	printf("13: %s", res);
	if (res)
		free(res);
	res = get_next_line(fd2);
	printf("14: %s", res);
	if (res)
		free(res);
	res = get_next_line(fd3);
	printf("15: %s", res);
	if (res)
		free(res);
	// res = get_next_line(fd2);
	// printf("4: %s", res);
	// free(res);
	// res = get_next_line(fd);
	// printf("5: %s", res);
	// free(res);
	// res = get_next_line(fd2);
	// printf("6: %s", res);
	// free(res);
	// res = get_next_line(fd);
	// printf("7: %s", res);
	// free(res);
	// res = get_next_line(fd2);
	// printf("8: %s", res);
	// free(res);

	// res = get_next_line(fd);
	// printf("9: %s", res);
	// free(res);
	// res = get_next_line(fd2);
	// printf("10: %s", res);
	// free(res);
	// res = get_next_line(fd);
	// printf("11: %s", res);
	// free(res);
	// res = get_next_line(fd2);
	// printf("12: %s", res);
	// free(res);

	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}
