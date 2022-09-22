#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

int indexA = 1;
void	gnl(int fd, char *data)
{
	char *res = get_next_line(fd);
	if (!res && !data)
	{
		printf("%d - GOOD [%s|%s]\n", indexA, res, data);
		++indexA;
		return ;
	}
	if (strcmp(res, data) == 0)
		printf("%d - GOOD [%s|%s]\n", indexA, res, data);
	else
		printf("%d - KO [%s|%s]\n", indexA, res, data);
	++indexA;
	if (res)
	{
		free(res);
		res = NULL;
	}
}

int		main(int ac, char **av)
{
	(void)ac;
	char	*res;
	int		fd = open(av[1], O_RDONLY);

	// fd[0] = open("gnlTester/files/41_with_nl", O_RDWR);
	// /* 1 */ gnl(1000, NULL);
	// /* 2 */ gnl(fd[0], "0123456789012345678901234567890123456789\n");

	// fd[1] = open("gnlTester/files/42_with_nl", O_RDWR);
	// /* 3 */ gnl(1001, NULL);
	// /* 4 */ gnl(fd[1], "01234567890123456789012345678901234567890\n");

	// fd[2] = open("gnlTester/files/43_with_nl", O_RDWR);
	// /* 5 */ gnl(1002, NULL);
	// /* 6 */ gnl(fd[2], "012345678901234567890123456789012345678901\n");

	// /* 7 */ gnl(1003, NULL);
	// /* 8 */ gnl(fd[0], "0");

	// /* 9 */ gnl(1004, NULL);
	// /* 10 */ gnl(fd[1], "1");

	// /* 11 */ gnl(1005, NULL);
	// /* 12 */ gnl(fd[2], "2");

	// /* 13 */ gnl(fd[0], NULL);
	// /* 14 */ gnl(fd[1], NULL);
	// /* 15 */ gnl(fd[2], NULL);

	// fd[3] = open("gnlTester/files/nl", O_RDWR);
	// /* 16 */ gnl(1006, NULL);
	// /* 17 */ gnl(fd[3], "\n");
	// /* 18 */ gnl(1007, NULL);
	// /* 19 */ gnl(fd[3], NULL);

	while ((res = get_next_line(fd)))
	{
		printf("%s", res);
		free(res);
	}
	printf("%s", res);
	// res = get_next_line(1000);
	// printf("1: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(-1);
	// printf("2: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(fd);
	// printf("3: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(fd2);
	// printf("4: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(1002);
	// printf("5: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(fd3);
	// printf("6: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(1003);
	// printf("7: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(fd);
	// printf("8: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(1004);
	// printf("9: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(fd2);
	// printf("10: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(1005);
	// printf("11: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(fd3);
	// printf("12: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(fd);
	// printf("13: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(fd2);
	// printf("14: %s", res);
	// if (res)
	// 	free(res);
	// res = get_next_line(fd3);
	// printf("15: %s", res);
	// if (res)
	// 	free(res);
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
	return (0);
}
