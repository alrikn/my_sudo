/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "my.h"
#include "struct.h"

void check_input_validity(core_t *fm, int start, int end)
{
    if (start >= end && fm->flag.s_flag == false &&
    fm->flag.E_flag == false) {
        print_instructions(84);
    }
}

int check_user_validity(core_t *fm)
{
    if (sudoers_check(fm) != 0) {
        printf("%s is not in the.*sudoers file\n", fm->username);
        exit(84);
    }
    if (fm->too_cool == true)
        return 0;
    if (fm->username != NULL && verify_password(fm) != 1) {
        return 0;
    } else {
        printf("failed to find user\n");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv, char **env)
{
    char *phrase = NULL;
    int i = 0;
    core_t fm = {0};

    fm.env_array = arrdup(env);
    flags(&i, argc, argv, &fm);
    check_input_validity(&fm, i, argc);
    if (fm.flag.h_flag == true)
        print_instructions(0);
    if (check_user_validity(&fm) == 1)
        return 84;
    if (sort_flags(&fm, argv, argc, &i) == 1)
        return 84;
    phrase = array_to_phrase(argv, i, argc);
    system(phrase);
    free(phrase);
    return 0;
}
