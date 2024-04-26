# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 15:48:32 by fcoullou          #+#    #+#              #
#    Updated: 2024/03/27 14:34:11 by fcoullou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------#
NAME			= client									
NAME2			= server									
#------------------------------------------------#
SRC_PATH		= src
INC_PATH		= include
OBJ_PATH		= obj

LIBFT_D			= ./libft
LIBFT			= ./libft/libft.a

SRC				= $(wildcard $(SRC_PATH)/*.c)
OBJ				= $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
#------------------------------------------------#
AR				= ar
CC				= cc
RM				= rm -f
CD				= cd
DIR_DUP			= mkdir -p $(@D)
#------------------------------------------------#
CFLAGS			= -Wall -Werror -Wextra -I./include  -I./libft/include -g3
LFLAGS 			= -L./libft -lft
#------------------------------------------------#
all: $(NAME) $(NAME2)

$(NAME): $(LIBFT) obj/client.o obj/utils.o
	@$(CC) $(CFLAGS) obj/client.o obj/utils.o -o $(NAME) $(LFLAGS) 
	@printf "CREATED $@\n"
	
$(NAME2): $(LIBFT) obj/server.o obj/utils.o
	@$(CC) $(CFLAGS) obj/server.o obj/utils.o -o $(NAME2) $(LFLAGS) 
	@printf "CREATED $@\n"

echo:
	echo $(CFLAGS)

$(LIBFT):
	@make -C $(LIBFT_D)
	@printf "CREATED $@\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c $< -o $@ 
	@printf "CREATED $@\n"

clean:
	make -C $(LIBFT_D) clean
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_PATH)
	$(RM) $(LIBFT_D)/%.o

fclean: clean
	make -C $(LIBFT_D) fclean
	$(RM) $(NAME)
	$(RM) $(NAME2)
	
re: fclean all
#------------------------------------------------#
.PHONY: show fclean clean all
#------------------------------------------------#
