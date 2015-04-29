# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/28 12:54:53 by tcoppin           #+#    #+#              #
#    Updated: 2015/04/29 04:13:37 by tcoppin          ###   ########.fr        #
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

SRC_SV	=	server.c server_error.c
SRC_CL	=	client.c client_error.c

OBJ_SV	=	$(SRC_SV:.c=.o)
OBJ_CL	=	$(SRC_CL:.c=.o)

INC 		= ft_p.h
LIBFLAGS 	= -L./libft/ -lft
SRCDIR  	= ./srcs/
OBJDIR  	= ./obj/
INCDIRLIB	= ./libft/includes/
INCDIR		= ./includes/
SRCS_SV		= $(addprefix $(SRCDIR), $(SRC_SV))
OBJS_SV		= $(addprefix $(OBJDIR), $(OBJ_SV))
SRCS_CL		= $(addprefix $(SRCDIR), $(SRC_CL))
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
