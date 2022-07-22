#include "minirt.h"

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	printf("hello world!\n");
	return (0);
}

void	ft_error(const char *errmsg, int errcode)
{
	write(2, "Error\n", 6);
	write(2, errmsg, ft_strlen(errmsg));
	exit(errcode);
}
