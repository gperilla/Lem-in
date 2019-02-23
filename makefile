# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperilla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 16:43:17 by gperilla          #+#    #+#              #
#    Updated: 2018/02/16 13:53:32 by gperilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = gcc

WARNINGS = -Werror -Wextra -Wall

INC = -I. -I libft/ -I libft/ft_printf/

LIB = -L libft/ -lft \

OBJC = 	main.c \
		for_the_norm.c \
		les_voisins.c \
		record.c \
		resolv.c \

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
	$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	tput smso
	tput smul
	@echo '[Run it you fool]'
	@tput sgr0
endef

all: $(NAME)
ifndef SILENT
	@tput smso
	@$(call ISOK, $@)
endif
	@:

$(NAME): $(OBJ)
ifndef SILENT
	@make -C libft
	@make -C visu
endif
	@$(CC) $(INC) $(WARNINGS) $(LIB) $(OBJ) -o $@

test:
	@make -j4 -C libft SILENT=1
	@make -j4 -C visu test SILENT=1
	@$(CC) $(INC) $(LIB) $(OBJC) -o $(NAME)
	@tput smso
	@echo 'test it'

fast:
	@make -j4 -C libft SILENT=1
	@make -j4 -C visu SILENT=1
	@make SILENT=1
	@tput smso
	@echo 'ready for action'

%.o: %.c
	@gcc -c $(INC) $(WARNINGS) $< -o $@
ifndef SILENT
	$(call OK, $*)
endif

clean:
	@make -C libft clean
	@make -C visu clean
	@rm -f $(OBJ)
	@echo 'removed .o'

fclean: clean
	@make -C libft fclean
	@make -C visu fclean
	@rm -rf $(NAME)
	@echo 'All your base are belong to us'

re: fclean all

.PHONY: all clean fclean re test
