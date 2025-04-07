/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** confirm_group
*/

#include <my.h>

int confirm_group(char *group_name)
{
    FILE *passwd_file = fopen("/etc/group", "r");
    char *group = NULL;
    char *line = NULL;
    size_t len = 0;

    if (passwd_file == NULL)
        return 1;
    while (getline(&line, &len, passwd_file) != -1) {
        group = strtok(line, ":");
        if (contains(group, group_name) == 0)
            return 0;
    }
    fclose(passwd_file);
    free(line);
    return 1;
}
