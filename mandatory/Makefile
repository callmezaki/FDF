NAME = fdf
INCLUDE = fdf.h
SRC = 	fdf.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_split.c \
		get_next_line_utils.c \
		get_next_line.c \
		ft_strtrim.c \
		ft_strlcpy.c \
		ft_strncmp.c \
		ft_atoi.c \
		fdf_tools.c \
		fdf_tools2.c \

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)
$(NAME): $(INCLUDE) $(SRC:.c=.o)
	@gcc  $(SRC) -I $(INCLUDE) -o $(NAME)  -lmlx -framework OpenGL -framework AppKit
clean:
	rm -f $(SRC:.c=.o)
fclean: clean
	rm -f $(NAME)
re: fclean all