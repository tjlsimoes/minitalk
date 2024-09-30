# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 15:15:50 by tjorge-l          #+#    #+#              #
#    Updated: 2024/09/24 15:40:04 by tjorge-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minitalk
SERVER_NAME := server
CLIENT_NAME := client

LIBFT := libft/libft.a
PRINTF := printf/libftprintf.a

CC := cc

CFLAGS := -Wall -Wextra -Werror
DEBUG_FLAGS = -g

SERVER_SRC := server.c

SERVER_OBJ := $(SERVER_SRC:.c=.o)

CLIENT_SRC := client.c

CLIENT_OBJ := $(CLIENT_SRC:.c=.o)

all: $(NAME)

$(NAME): $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJ)
	cd printf && $(MAKE)
	cd libft && $(MAKE)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(PRINTF) $(LIBFT) -o $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJ)
	cd printf && $(MAKE)
	cd libft && $(MAKE)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(PRINTF) $(LIBFT) -o $(CLIENT_NAME)

clean:
	cd printf && $(MAKE) clean
	cd libft && $(MAKE) clean
	$(RM) $(OBJ) $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	cd printf && $(MAKE) fclean
	cd libft && $(MAKE) fclean
	$(RM) $(SERVER_NAME) $(CLIENT_NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean debug re

# $(OBJ)
# 	cd printf && $(MAKE)
# 	cd libft && $(MAKE)
# 	$(CC) $(CFLAGS) $(OBJ) $(PRINTF) $(LIBFT) -o $(NAME)
## $(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# bonus: $(CHECKER_NAME)

# $(CHECKER_NAME): $(CHECKER_OBJ)
# 	cd printf && $(MAKE)
# 	cd libft && $(MAKE)
# 	$(CC) $(CFLAGS) $(CHECKER_OBJ) $(PRINTF) $(LIBFT) -o $(CHECKER_NAME)
# ## $(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# clean:
# 	cd printf && $(MAKE) clean
# 	cd libft && $(MAKE) clean
# 	$(RM) $(OBJ) $(CHECKER_OBJ)

# fclean: clean
# 	cd printf && $(MAKE) fclean
# 	cd libft && $(MAKE) fclean
# 	$(RM) $(NAME) $(CHECKER_NAME)

# debug: CFLAGS += $(DEBUG_FLAGS)
# debug: $(OBJ)
# 	cd printf && $(MAKE)
# 	cd libft && $(MAKE) debug
# 	$(CC) -g $(CFLAGS) $(OBJ) $(PRINTF) $(LIBFT) -o $(NAME)

# bdebug: CFLAGS += $(DEBUG_FLAGS)
# bdebug: $(CHECKER_OBJ)
# 	cd printf && $(MAKE)
# 	cd libft && $(MAKE) debug
# 	$(CC) $(CFLAGS) $(CHECKER_OBJ) $(PRINTF) $(LIBFT) -o $(CHECKER_NAME)

# .PHONY: all bonus debug bdebug clean fclean re
# https://www.baeldung.com/linux/a-so-extension-files
# https://medium.com/@ayogun/makefile-basics-beginner-intermediate-c92377542c2c