/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** struct
*/

#ifndef INCLUDED_STRUCT_H
    #define INCLUDED_STRUCT_H
    #include <stdbool.h>

typedef struct flag flag_t;
typedef struct flag {
    bool h_flag;
    bool s_flag;
    bool u_flag;
    bool g_flag;
    bool E_flag;
    bool skip;
} flag_t;

typedef struct environnement {
    char *home;
    char *log_name;
    char *path;
    char *user;
    char *shell;
} env_t;

typedef struct fake_user {
    char *fake_user_uid;
    char *fake_user_gid;
    int fake_uid;
    int fake_gid;
} fake_t;

typedef struct core core_t;

typedef struct core {
    bool too_cool;
    char *username;
    char *shell;
    char **env_array;
    int real_uid;
    fake_t fake;
    flag_t flag;
    env_t env;
} core_t;


#endif
