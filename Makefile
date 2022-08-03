# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuhwang <yuhwang@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 18:52:34 by yuhwang           #+#    #+#              #
#    Updated: 2022/08/03 18:52:35 by yuhwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	miniRT
LIBFTDIR		=	./libft
LIBFTFILE		=	libft.a
MINILIBXDIR		=	./minilibx_mms
MINILIBXLIB		=	libmlx.dylib

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror# -fsanitize=address -g
RM				=	rm -f

SRCS			=	minirt.c				\
					get_next_line.c			\
					mlx_setting.c			\
					drawing.c				\
					ft_boolean.c			\
					hit_cylinder.c			\
					hit_plane.c				\
					hit_sphere.c			\
					hit.c					\
					init.c					\
					obj_struct.c			\
					phong_lightning.c		\
					ray.c					\
					read_elements1.c		\
					read_elements2.c		\
					read_elements3.c		\
					read_elements4.c		\
					utils.c					\
					vector_constructor.c	\
					vector_operator1.c		\
					vector_operator2.c		\

OBJS			=	$(SRCS:.c=.o)

$(NAME)			:	$(OBJS)
					$(MAKE) bonus -C $(LIBFTDIR)
					$(MAKE) -C $(MINILIBXDIR)
					cp $(MINILIBXDIR)/$(MINILIBXLIB) .
					$(CC) $(CFLAGS) -o $@ $^ $(LIBFTDIR)/$(LIBFTFILE) $(MINILIBXLIB)

all				:	$(NAME)

%.o				:	%.c
					$(CC) $(CFLAGS) -o $@ -c $< -I./include/

clean			:
					$(MAKE) -C $(LIBFTDIR) fclean
					$(MAKE) -C $(MINILIBXDIR) clean
					$(RM) $(MINILIBXDIR)/mlx_image.swiftsourceinfo
					$(RM) $(MINILIBXDIR)/mlx_init.swiftsourceinfo
					$(RM) $(MINILIBXDIR)/mlx_window.swiftsourceinfo
					$(RM) $(OBJS)

fclean			:	clean
					$(RM) $(NAME) $(MINILIBXLIB)

re				:
					$(MAKE) fclean
					$(MAKE) all

.PHONY			:	all clean fclean re
