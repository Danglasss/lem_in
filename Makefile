# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danglass <danglass@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/18 14:29:33 by nabboufe          #+#    #+#              #
#    Updated: 2019/12/26 19:19:58 by danglass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		lem-in

LIBFT_A		=		libft.a

INCLUDES	=		-Iinclude

SRCS		=		srcs/main.c					\
					srcs/chained_list.c			\
					srcs/bfs.c					\
					srcs/create_room.c			\
					srcs/list_pos.c				\
					srcs/add_list.c				\
					srcs/colision.c				\
					srcs/check_insert.c			\
					srcs/is_int.c				\
					srcs/initialisation.c		\
					srcs/t_hash.c				\
					srcs/repartition.c			\
					srcs/free.c					\
					srcs/print.c				\
					srcs/leaks.c				\
					srcs/edmonds.c				\

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
