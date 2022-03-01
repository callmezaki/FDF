NAME = fdf
INCLUDE = mandatory/fdf.h
INCLUDE_B = bonus/fdf_bonus.h
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

SRC_B =		bonus/fdf_bonus.c \
		bonus/ft_strdup_bonus.c \
		bonus/ft_strlen_bonus.c \
		bonus/ft_split_bonus.c \
		bonus/get_next_line_utils_bonus.c \
		bonus/get_next_line_bonus.c \
		bonus/ft_strtrim_bonus.c \
		bonus/ft_strlcpy_bonus.c \
		bonus/ft_strncmp_bonus.c \
		bonus/ft_atoi_bonus.c \
		bonus/fdf_tools_bonus.c \
		bonus/fdf_tools2_bonus.c \
		bonus/ft_itoa_bonus.c \
		bonus/fdf_hooks_bonus.c \
		bonus/fdf_rotation_bonus.c \
		bonus/ft_mlx_bonus.c \
		bonus/map_check_bonus.c \
		bonus/fdf_drawing_bonus.c \
		bonus/fdf_drawing2_bonus.c \

CFLAGS = -Wall -Werror -Wextra

OBJS = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@rm -f  $(OBJ_B) $(NAME)
	@gcc  $(CFLAGS) -I $(INCLUDE) -o $@ $^   -lmlx -framework OpenGL -framework AppKit

bonus : $(OBJ_B)
	@rm -f  $(OBJS) $(NAME)
	@gcc  $(CFLAGS) -I $(INCLUDE_B) -o $(NAME) $^  -lmlx -framework OpenGL -framework AppKit

clean:
	@rm -f $(OBJS) $(OBJ_B)
fclean: clean
	@rm -f $(NAME)
re: fclean all