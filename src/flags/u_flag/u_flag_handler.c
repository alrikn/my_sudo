/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** u_flag_handler
*/

#include "my.h"
#include "struct.h"
#include <string.h>

int u_flag_handler(core_t *fm, char **argv, int *start, int end)
{
    char *fake_user = NULL;
    int i = 0;

    if (*start > end) {
        print_instructions(84);
    }
    for (i = 0; i < *start; i++) {
        if (contains(argv[i], "-u") == 0) {
            i++;
            fake_user = argv[i];
            break;
        }
    }
    if (change_uid(fake_user, fm) != 0) {
        printf("my_sudo: unknown user %s\n", fake_user);
        exit(84);
    }
    return 0;
}
