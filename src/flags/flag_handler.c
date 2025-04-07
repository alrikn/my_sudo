/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** flag_handler
*/

#include "my.h"
#include "struct.h"
#include <stdbool.h>
#include <string.h>

static int useless_g_checker(core_t *fm, char **argv, int *start)
{
    *start += 1;
    if (fm->username && argv[*start]) {
        if (strcmp(fm->username, argv[*start]) == 0) {
            fm->too_cool = true;
            fm->flag.skip = true;
        }
        if (confirm_group(argv[*start]) == 1) {
            printf("my_sudo: unknown group %s\n", argv[*start]);
            exit(84);
        }
    } else {
        print_instructions(84);
    }
    return 0;
}

static int useless_u_checker(core_t *fm, char **argv, int *start)
{
    *start += 1;
    if (fm->username && argv[*start]) {
        if (strcmp(fm->username, argv[*start]) == 0) {
            fm->too_cool = true;
            fm->flag.skip = true;
        }
        if (confirm_user(argv[*start]) == 1) {
            printf("my_sudo: unknown user %s\n", argv[*start]);
            exit(84);
        }
    } else {
        print_instructions(84);
    }
    return 0;
}

void update_flag_struct(char *str, core_t *fm, int *start, char **argv)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == 'h')
            print_instructions(0);
        if (str[i] == 'u') {
            fm->flag.u_flag = true;
            useless_u_checker(fm, argv, start);
        }
        if (str[i] == 'E')
            fm->flag.E_flag = true;
        if (str[i] == 's')
            fm->flag.s_flag = true;
        if (str[i] == 'g') {
            fm->flag.g_flag = true;
            useless_g_checker(fm, argv, start);
        }
    }
}

int flags(int *i, int argc, char **argv, core_t *fm)
{
    if (argc < 2)
        print_instructions(84);
    fm->username = find_user(fm);
    for (*i = 1; *i < argc; (*i)++) {
        if (argv[*i][0] == '-') {
            update_flag_struct(argv[*i], fm, i, argv);
        } else
            return 1;
    }
    return 0;
}
