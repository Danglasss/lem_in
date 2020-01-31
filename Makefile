# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damboule <damboule@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/18 14:29:33 by dygouin           #+#    #+#              #
#    Updated: 2020/01/31 18:18:43 by dygouin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		lem-in

LIBFT_A		=		libft.a

INCLUDES	=		-Iinclude

SRCS		=		srcs/main.c					\
					srcs/chained_list.c			\
					srcs/clean_map.c			\
					srcs/bfs.c					\
					srcs/create_room.c			\
					srcs/list_pos.c				\
					srcs/add_list.c				\
					srcs/colision.c				\
					srcs/check_insert.c			\
					srcs/is_int.c				\
					srcs/initialisation.c		\
					srcs/t_hash.c				\
					srcs/reset_transfert.c		\
					srcs/free.c					\
					srcs/print.c				\
					srcs/leaks.c				\
					srcs/affichage.c			\
					srcs/edmonds.c				\
					srcs/linksvalue.c			\
					srcs/printpath.c			\

OBJ			=		$(SRCS:.c=.o)

CC			=		gcc

CFLAGS		=

DECHET		=		*.dSYM

all			:		$(LIBFT_A) $(NAME)

$(LIBFT_A)	:		
	@make -C libft/ all clean >/dev/null
	@echo "libft compilation is done !\n"
	@mv libft/libft.a .

$(NAME)		:		$(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(LIBFT_A) $(OBJ) $(INCLUDES) -o $(NAME)
	@rm -rf $(DECHET)

clean		:
	@rm -rf $(OBJ) $(DECHET)
	@echo "clean completed !"

fclean		:		clean
	@rm -rf $(NAME) $(LIBFT_A) $(DECHET) &>/dev/null
	@echo "fclean completed !\n"

re			:		fclean all

.PHONY		:		fclean all
