NAME = fdf
INCLUDE = mandatory/fdf.h
INCLUDE_B = bonus/fdf.h
SRC =	mandatory/fdf.c \
		mandatory/ft_strdup.c \
		mandatory/ft_strlen.c \
		mandatory/ft_split.c \
		mandatory/get_next_line_utils.c \
		mandatory/get_next_line.c \
		mandatory/ft_strtrim.c \
		mandatory/ft_strlcpy.c \
		mandatory/ft_strncmp.c \
		mandatory/ft_atoi.c \
		mandatory/fdf_tools.c \
		mandatory/fdf_tools2.c \
		mandatory/fdf_drawing.c \
		mandatory/fdf_drawing2.c \
		mandatory/handle_map.c \
		mandatory/fdf_hooks.c  \

SRC_B =		bonus/fdf.c \
		bonus/ft_strdup.c \
		bonus/ft_strlen.c \
		bonus/ft_split.c \
		bonus/get_next_line_utils.c \
		bonus/get_next_line.c \
		bonus/ft_strtrim.c \
		bonus/ft_strlcpy.c \
		bonus/ft_strncmp.c \
		bonus/ft_atoi.c \
		bonus/fdf_tools.c \
		bonus/fdf_tools2.c \
		bonus/ft_itoa.c \
		bonus/fdf_hooks.c \
		bonus/fdf_rotation.c \
		bonus/ft_mlx.c \
		bonus/map_check.c \
		bonus/fdf_drawing.c \
		bonus/fdf_drawing2.c \

CFLAGS = -Wall -Werror -Wextra

OBJS = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
#	@rm -f  $(OBJ_B) $(NAME)
	@gcc  $(CFLAGS) -I $(INCLUDE) -o $@ $^   -lmlx -framework OpenGL -framework AppKit

bonus : $(OBJ_B)
	@make fclean
	@gcc  $(CFLAGS) -I $(SRC_B) $(INCLUDE_B) -o $(NAME) $^   -lmlx -framework OpenGL -framework AppKit

clean:
	@rm -f $(OBJS) $(OBJ_B)
fclean: clean
	@rm -f $(NAME)
re: fclean all