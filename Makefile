NAME			=	miniRT
LIBFTDIR		=	../libft
LIBFTFILE		=	libft.a
MINILIBXDIR		=	./minilibx_mms
MINILIBXLIB		=	libmlx.dylib

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -f

SRCS			=	minirt.c		\
					get_next_line.c	\

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
