/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** confirm_user
*/

#include "my.h"

int confirm_user(char *user)
{
    FILE *passwd_file = fopen("/etc/passwd", "r");
    char *username = NULL;
    char *line = NULL;
    size_t len = 0;

    if (passwd_file == NULL)
        return 1;
    while (getline(&line, &len, passwd_file) != -1) {
        username = strtok(line, ":");
        if (contains(username, user) == 0)
            return 0;
    }
    fclose(passwd_file);
    free(line);
    return 1;
}
