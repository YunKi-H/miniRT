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
// sqrt pow fmax ..
# include "../libft/libft.h"
# include "get_next_line.h"

void	ft_error(const char *errmsg, int errcode);

#endif
