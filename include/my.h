/*
** EPITECH PROJECT, 2024
** fake_my_hunter
** File description:
** my
*/

#ifndef INCLUDED_MY_H
    #define INCLUDED_MY_H
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <struct.h>
    #include <crypt.h>
    #define MAX_BUFFER 1024
char *array_to_phrase(char **arr, int start, int end);
char **arrdup(char **array);
void free_array(char **array);
char *num_to_str(long num);
char *find_user(core_t *fm);
int verify_password(core_t *fm);
int contains(const char *big, const char *small);
int flags(int *i, int argc, char **argv, core_t *fm);
int sudoers_check(core_t *fm);
int sort_flags(core_t *fm, char **argv, int argc, int *i);
void print_instructions(int status);
int u_flag_handler(core_t *fm, char **argv, int *start, int end);
int g_flag_handler(core_t *fm, char **argv, int *start, int end);
int s_flag_handler(core_t *fm, char **argv, int *start, int end);
int confirm_user(char *user);
int change_uid(char *user_name, core_t *fm);
int change_gid(char *user_name, core_t *fm);
int save_gid(char *user, core_t *fm);
int confirm_group(char *group_name);
#endif
