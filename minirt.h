#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
// write read
# include <stdlib.h>
// malloc free exit
# include <stdio.h>
// printf perror strerror
# include <fcntl.h>
// open close
# include <math.h>

#include "../libft/libft.h"

void	ft_error(const char *errmsg, int errcode);

#endif
