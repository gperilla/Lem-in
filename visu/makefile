# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperilla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 16:43:17 by gperilla          #+#    #+#              #
#    Updated: 2018/02/19 17:00:03 by gperilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lemin_visu

CC = gcc

WARNINGS = -Werror -Wextra -Wall

INC = -I. -I libft/ -I libft/ft_printf/

LIB = -L ../libft/ -lft \
	  -L minilibx_macos -lmlx -framework OpenGL -framework appKit \

OBJC = main.c \
	   putpixel.c \
	   draw_line.c \
	   draw_circle.c \
	   drawing1.c \
	   drawing2.c \
	   recording.c \

OBJ = $(OBJC:.c=.o)

COLOR = $(shell bash -c 'echo $$RANDOM')

define OK
	@$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	@echo -n $1
	$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	@echo ' [Compiled]'
	@tput sgr0
endef

define ISOK
	@$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	@echo $1 '[Ready]'
endef

all: $(NAME)
ifndef SILENT
	@$(call ISOK, $(NAME))
endif
	@:

$(NAME): $(OBJ)
	@make --silent -C minilibx_macos
	@make -C ../libft
	@$(CC) $(INC) $(WARNINGS) $(LIB) $(OBJ) -o $@


test:
	@make --silent -C minilibx_macos
	@make -j4 -C ../libft SILENT=1
	@$(CC) $(INC) $(LIB) $(OBJC) -o $(NAME)
	@tput smso
	@echo 'test it'

fast:
	@make --silent -C minilibx_macos
	@make -j4 -C ../libft SILENT=1
	@make SILENT=1
	@tput smso
	@echo 'ready for action'
	@tput setaf sgr0

%.o: %.c
	@gcc -c $(INC) $(WARNINGS) $< -o $@
ifndef SILENT
	$(call OK, $*)
endif

clean:
	@make -C ../libft clean
	@rm -f $(OBJ)
	@echo 'removed .o'

fclean: clean
	@make --silent -C minilibx_macos clean
	@make -C ../libft fclean
	@rm -rf $(NAME)
	@echo 'All your base are belong to us'

re: fclean all

.PHONY: all clean fclean re test
