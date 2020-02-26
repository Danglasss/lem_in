# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damboule <damboule@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/18 14:29:33 by dygouin           #+#    #+#              #
#    Updated: 2020/02/26 15:51:51 by dygouin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		lem-in

LIBFT_A		=		./libft/libft.a

INCLUDES	=		-Iinclude -Ilibft/includes

DIR_SRCS	=		./srcs/

SRCS		=		main.c					\
					chained_list.c			\
					clean_map.c				\
					bfs.c					\
					create_room.c			\
					list_pos.c				\
					add_list.c				\
					colision.c				\
					check_insert.c			\
					is_int.c				\
					initialisation.c		\
					t_hash.c				\
					reset_transfert.c		\
					free.c					\
					leaks.c					\
					affichage.c				\
					edmonds.c				\
					linksvalue.c			\
					printpath.c				\
					repartition.c			\
					linkscondition.c		\
					correctionpath.c		

vpath		%.c		$(DIR_SRCS)

HEAD		=		include/lem_in.h

DIR_OBJS	=		./objs/

OBJ			=		$(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))

CC			=		clang

CFLAGS		=		-Wall -Wextra -Werror

DECHET		=		*.dSYM

all			:		$(NAME)


$(DIR_OBJS) :
		mkdir $@

$(OBJ)		: $(DIR_OBJS)%.o : %.c $(HEAD)
		$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) 

$(LIBFT_A)	: FORCE	
	$(MAKE) -C libft/

FORCE		:

$(NAME)		:		$(DIR_OBJS) $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(LIBFT_A) $(OBJ) $(INCLUDES) -o $(NAME)

clean		:
	$(RM) -R $(DIR_OBJS) $(DECHET)
	$(MAKE) clean -C  libft
	echo "clean completed!"

fclean		:		clean
	$(RM) -R $(NAME) $(LIBFT_A) $(DECHET)
	$(MAKE) fclean -C libft
	echo "fclean completed!"

re			:		fclean
	$(MAKE)

.PHONY		:		all clean fclean re FORCE
