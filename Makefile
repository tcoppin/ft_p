# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/28 12:54:53 by tcoppin           #+#    #+#              #
#    Updated: 2015/07/23 15:49:42 by tcoppin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		=	server
CLIENT		=	client

DEBUG		= no
ifeq ($(DEBUG),no)
	FLAGS	= -Wall -Werror -Wextra
else
	FLAGS	= -g3
endif

SRC_SV	=	server.c misc_server.c init_server.c ft_cd.c exec_server.c \
			ft_to_client.c ft_check.c get_server.c
SRC_CL	=	client.c misc_client.c init_client.c ft_to_server.c exec_client.c \
			ft_check.c ft_cd_client.c get_client.c

OBJ_SV	=	$(SRC_SV:.c=.o)
OBJ_CL	=	$(SRC_CL:.c=.o)

INC 		= ft_p.h
LIBFLAGS 	= -L./libft/ -lft
SRCDIR_SV	= ./srcs/server/
SRCDIR_CL	= ./srcs/client/
OBJDIR  	= ./obj/
INCDIRLIB	= ./libft/includes/
INCDIR		= ./includes/
SRCS_SV		= $(addprefix $(SRCDIR_SV), $(SRC_SV))
OBJS_SV		= $(addprefix $(OBJDIR), $(OBJ_SV))
SRCS_CL		= $(addprefix $(SRCDIR_CL), $(SRC_CL))
OBJS_CL		= $(addprefix $(OBJDIR), $(OBJ_CL))

.SILENT:

all : 		server client

$(SERVER) :
ifeq ($(DEBUG),yes)
		echo "\\033[1;31mDEBUG COMPILATION.. (no flags except -g)\\033[0;39m"
else
		echo "\\033[1;31mCompilation of server with -Wall -Wextra -Werror...\\033[0;39m"
endif
		echo "\\033[1;34mGenerating server's objects... Please wait.\\033[0;39m"
		Make -C libft/
			gcc $(FLAGS) -c $(SRCS_SV) -I $(INCDIR) -I $(INCDIRLIB)
			echo "compiling $(SERVER)..."
			mkdir -p $(OBJDIR)
			mv $(OBJ_SV) $(OBJDIR)
			gcc $(FLAGS) -o $(SERVER) $(OBJS_SV) $(LIBFLAGS)
			echo "$(SERVER) has been created !"

$(CLIENT) :
ifeq ($(DEBUG),yes)
		echo "\\033[1;31mDEBUG COMPILATION.. (no flags except -g)\\033[0;39m"
else
		echo "\\033[1;31mCompilation of client with -Wall -Wextra -Werror...\\033[0;39m"
endif
		echo "\\033[1;34mGenerating client's objects... Please wait.\\033[0;39m"
		Make -C libft/
			gcc $(FLAGS) -c $(SRCS_CL) -I $(INCDIR) -I $(INCDIRLIB)
			echo "compiling $(CLIENT)..."
			mkdir -p $(OBJDIR)
			mv $(OBJ_CL) $(OBJDIR)
			gcc $(FLAGS) -o $(CLIENT) $(OBJS_CL) $(LIBFLAGS)
			echo "$(CLIENT) has been created !"

.PHONY: 	clean fclean re

clean : 
			Make -C ./libft/ clean
			rm -rf $(OBJS_SV)
			rm -rf $(OBJS_CL)
			rm -rf $(OBJDIR)
			echo "objects files has been removed !"

fclean :	clean
			Make -C ./libft/ fclean
			rm -rf $(SERVER)
			rm -rf $(CLIENT)
			echo "$(SERVER) has been removed !"
			echo "$(CLIENT) has been removed !"

re		: 	fclean all

git :
			git add .
			echo "Enter Your Commit : "
			read root_path ; git commit -m "$$root_path"
			git push
