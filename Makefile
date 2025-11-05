NAME = scop

SRCS_DIR = srcs/
OBJS_DIR = objs/

SRCS_LIST = main.cpp \
			parser.cpp \

SRCS = $(addprefix ${SRCS_DIR}, ${SRCS_LIST}),

CC = g++
CC_CFLAGS = -Wall -Wextra -Werror -lGL


all: ${OBJS}

${NAME}: all

%.o: %.cpp


.phony: all, re, clean, fclean