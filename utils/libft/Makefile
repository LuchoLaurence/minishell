AR = @ar rcs
CC = @gcc
CFLAGS = -Wall -Wextra -Werror
RM = @rm -f
NAME = libft.a

SRC =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJ = ${SRC:.c=.o}

SRC_B = ft_putnstr_printf.c ft_putchar_printf.c ft_putstr_printf.c ft_isspeci.c \
		ft_isflag.c ft_findlen.c ft_givespeci.c ft_isvalidflag.c ft_cutflag.c \
		ft_enew.c ft_printf.c ft_putnstr_nodouble.c ft_itoa_baseprintf.c \
		ft_itoa_i.c ft_strdup_pf.c ft_fillf.c ft_giveindex.c ft_putnstr_printf.c \
		ft_putelses.c

OBJ_B =	$(addprefix printf/, ${SRC_B:.c=.o})


all: $(NAME)

$(NAME): $(OBJ) $(OBJ_B)
	@echo "Compiling libft.a"
	$(AR) $(NAME) $(OBJ) $(OBJ_B)

.c.o:
	$(CC) $(CFLAGS) -I libft.h -c $< -o ${<:.c=.o}

clean:
	@echo "Removing Libft Objects"
	$(RM) $(OBJ) $(OBJ_B)

fclean: clean
	@echo "Removing libft.a"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean flclean re
