/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** gid_change
*/

#include "my.h"
#include "struct.h"
#include <unistd.h>

static int check(char *line, core_t *fm)
{
    char *gid_str = NULL;

    strtok(line, ":");
    strtok(NULL, ":");
    gid_str = strtok(NULL, ":");
    if (gid_str != NULL) {
        fm->fake.fake_gid = atoi(gid_str);
        free(line);
        return 0;
    }
    return 1;
}

int save_gid(char *user, core_t *fm)
{
    FILE *passwd_file = fopen("/etc/group", "r");
    char *groupname = NULL;
    char *line = NULL;
    char *line_copy = NULL;
    size_t len = 0;

    if (passwd_file == NULL || confirm_user(user) == 1)
        return 1;
    while (getline(&line, &len, passwd_file) != -1) {
        line_copy = strdup(line);
        groupname = strtok(line, ":");
        if (contains(user, groupname) == 0) {
            fclose(passwd_file);
            return check(line_copy, fm);
        }
    }
    free(line);
    fclose(passwd_file);
    return 1;
}

int change_gid(char *user_name, core_t *fm)
{
    if (save_gid(user_name, fm) != 0)
        return 1;
    setgid(fm->fake.fake_gid);
    setegid(fm->fake.fake_gid);
    return 0;
}
