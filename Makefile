##
## EPITECH PROJECT, 2024
## My_printf
## File description:
## Makefile
##

LIB_NAME = libmy.a
NAME = my_sudo
TEST_BIN = unit_tests

SRC = ./main.c \
	./src/permissions/find_username.c \
	./src/permissions/verification.c \
	./src/permissions/check_sudoers.c \
	./src/permissions/confirm_user.c \
	./src/permissions/confirm_group.c \
	./src/flags/flag_handler.c \
	./src/flags/flag_chooser.c \
	./src/flags/s_flag/s_flag_handler.c \
	./src/flags/u_flag/u_flag_handler.c \
	./src/flags/u_flag/uid_change.c \
	./src/flags/g_flag/g_flag_handler.c \
	./src/flags/g_flag/gid_change.c \
	./src/utils/my_array_to_str.c \
	./src/utils/duplicate_array.c \
	./src/utils/free_array.c \
	./src/utils/contain.c \

TEST_SRC = $(SRC) \
	./tests/test_my_printf.c

CC = gcc
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -g
INCLUDE_PATH = ./include/
LDFLAGS = -I$(INCLUDE_PATH)
TEST_LDFLAGS = $(LDFLAGS) --coverage -lcriterion
DESTINATION = -I$(INCLUDE_PATH) -L. -lmy -lcrypt



all: $(LIB_NAME) $(NAME)

$(NAME): $(LIB_NAME)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(DESTINATION)

$(LIB_NAME): $(OBJ)
	ar -rc $(LIB_NAME) $(OBJ)

$(TEST_BIN):
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_SRC) $(TEST_LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ)
	rm -f *.gc*

fclean: clean
	rm -f $(LIB_NAME)
	rm -f $(NAME)
	rm -f $(TEST_BIN)

set_perm:
	sudo chown root $(NAME)
	sudo chmod u+s $(NAME)

re: fclean $(LIB_NAME) $(NAME)

compile:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS)

coverage: tests_run
	gcovr -r .
	gcovr -r . --branches

.PHONY: all re compile coverage fclean clean
