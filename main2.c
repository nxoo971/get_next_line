#include "get_next_line_bonus.h"
#include <stdio.h>
#include <string.h>

void	ft_free(char **res)
{
	if (*res)
	{
		free(*res);
		*res = NULL;
	}
}

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
	int		fd2 = open(av[2], O_RDONLY);

	res = get_next_line(fd);
	printf("%s", res);
	if (res)
		ft_free(&res);

	res = get_next_line(fd2);
	printf("%s", res);
	if (res)
		ft_free(&res);

	res = get_next_line(fd);
	printf("%s", res);
	if (res)
		ft_free(&res);

	res = get_next_line(fd2);
	printf("%s", res);
	if (res)
		ft_free(&res);

	res = get_next_line(fd);
	printf("%s", res);
	if (res)
		ft_free(&res);

	res = get_next_line(fd2);
	printf("%s", res);
	if (res)
		ft_free(&res);

	res = get_next_line(fd);
	printf("%s", res);
	if (res)
		ft_free(&res);

	res = get_next_line(fd2);
	printf("%s", res);
	if (res)
		ft_free(&res);

	close(fd);
	close(fd2);
	return (0);
}
