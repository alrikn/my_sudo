/*
** EPITECH PROJECT, 2025
** mysudo-nilab.sayed
** File description:
** uid_change
*/

#include "my.h"
#include "struct.h"
#include <grp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int check(char *line, core_t *fm, char *username)
{
    char *uid_str = NULL;

    strtok(line, ":");
    strtok(NULL, ":");
    uid_str = strtok(NULL, ":");
    if (uid_str != NULL) {
        fm->fake.fake_uid = atoi(uid_str);
        setgroups(0, NULL);
        initgroups(username, fm->fake.fake_gid);
        setgid(fm->fake.fake_gid);
        setegid(fm->fake.fake_gid);
        setuid(fm->fake.fake_uid);
        seteuid(fm->fake.fake_uid);
        free(line);
        return 0;
    }
    return 1;
}

int change_uid(char *user_name, core_t *fm)
{
    FILE *passwd_file = fopen("/etc/passwd", "r");
    char *username = NULL;
    char *line = NULL;
    char *line_copy = NULL;
    size_t len = 0;

    if (passwd_file == NULL || confirm_user(user_name) == 1)
        return 1;
    while (getline(&line, &len, passwd_file) != -1) {
        line_copy = strdup(line);
        username = strtok(line, ":");
        if (contains(user_name, username) == 0) {
            save_gid(user_name, fm);
            fclose(passwd_file);
            return check(line_copy, fm, user_name);
        }
    }
    free(line);
    fclose(passwd_file);
    return 1;
}
