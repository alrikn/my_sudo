/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** find_username
*/

#include "my.h"
#include "struct.h"
#include <string.h>

static char *malloc_response(char *username, FILE *passwd_file, char *line)
{
    char *response = NULL;

    fclose(passwd_file);
    response = strdup(username);
    free(line);
    return response;
}

char *find_user(core_t *fm)
{
    FILE *passwd_file = fopen("/etc/passwd", "r");
    char *username = NULL;
    char *uid_str = NULL;
    char *line = NULL;
    size_t len = 0;

    fm->real_uid = getuid();
    if (passwd_file == NULL)
        return NULL;
    while (getline(&line, &len, passwd_file) != -1) {
        username = strtok(line, ":");
        strtok(NULL, ":");
        uid_str = strtok(NULL, ":");
        if (uid_str != NULL && atoi(uid_str) == fm->real_uid)
            return malloc_response(username, passwd_file, line);
    }
    fclose(passwd_file);
    free(line);
    return NULL;
}
