# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/23 18:46:40 by aashara-          #+#    #+#              #
#    Updated: 2022/01/28 22:06:27 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	:=	 	tester

# ------------  DIRECTORIES  ------------------------------------------------- #
TMP_DIR =		tmp
HDR_DIR =		../../ft/containers

# ------------  SOURCE FILES  ------------------------------------------------ #
PRE_FLS	=		

SRC_FLS	=		$(PRE_FLS) \
				main.cpp \

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(SRC_FLS)
OBJS	=		$(patsubst %.cpp,$(TMP_DIR)/%.o, $(SRCS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		clang++
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra -std=c++98
IFLGS	=		-I $(HDR_DIR)
DFLGS	=		-O0 -g
DEPFLGS	=		-MMD -MP

ifeq ($(findstring std,$(MAKECMDGOALS)),std)
	CFLGS += -DSTD
	NAME := $(NAME)_std
endif

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re std


all: $(NAME)

std: $(NAME)

-include $(DEPS)
$(TMP_DIR)/%.o: %.cpp | $(TMP_DIR)
	$(CC) $(DFLGS) $(CFLGS) $(DEPFLGS) -c -o $@ $< $(IFLGS)

$(TMP_DIR):
	mkdir -p $(TMP_DIR)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLGS)

clean:
	$(RM) $(TMP_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME)_std


re: fclean all
