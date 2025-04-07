/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** flag_chooser
*/

#include "my.h"
#include "struct.h"
#include <stdbool.h>
#include <unistd.h>
#include <grp.h>

void print_instructions(int status)
{
    printf("usage:\t./my_sudo -h\n");
    printf("usage:\t./my_sudo [-ugEs] [command [args ...]]\n");
    exit(status);
}

static void u_and_g_flags(core_t *fm, char **argv, int end, int *i)
{
    if (fm->flag.u_flag == true)
        u_flag_handler(fm, argv, i, end);
    else {
        if (fm->flag.g_flag == false) {
            setuid(0);
            seteuid(0);
            setgroups(0, NULL);
        }
    }
    if (fm->flag.g_flag == true)
        g_flag_handler(fm, argv, i, end);
    else {
        if (fm->flag.u_flag == false) {
            setgid(0);
            setegid(0);
        }
    }
}

int sort_flags(core_t *fm, char **argv, int end, int *i)
{
    if (fm->flag.h_flag == true)
        print_instructions(0);
    if (fm->flag.skip == false)
        u_and_g_flags(fm, argv, end, i);
    if (fm->flag.s_flag == true)
        s_flag_handler(fm, argv, i, end);
    return 0;
}
