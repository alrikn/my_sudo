/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** check_sudoers
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>


static void find_members(core_t *fm, char ***array,
    int *gr_count, char *group_name)
{
    char *members = strtok(NULL, "\n");

    if (members && strstr(members, fm->username)) {
        *array = realloc(*array, (*gr_count + 1) * sizeof(char *));
        if (!*array)
            return;
        (*array)[*gr_count] = strdup(group_name);
        (*gr_count)++;
    }
}

int find_groups(FILE *group_file, char ***array, int *gr_count, core_t *fm)
{
    char line[256];
    char *group_name;

    while (fgets(line, sizeof(line), group_file)) {
        group_name = strtok(line, ":");
        strtok(NULL, ":");
        strtok(NULL, ":");
        find_members(fm, array, gr_count, group_name);
    }
    if (!*array)
        return 1;
    return 0;
}

static int loop_check(int group_count, char **array, char *line)
{
    char group_line[256];
    int has_sudo = 1;

    for (int i = 0; i < group_count; i++) {
        snprintf(group_line, sizeof(group_line), "%%%s", array[i]);
        if (contains(line, group_line) == 0) {
            has_sudo = 0;
            break;
        }
    }
    return has_sudo;
}

int find_sudoers(FILE *sudoers_file, core_t *fm, int group_count, char **array)
{
    int has_sudo = 1;
    char line[256];
    char uid_str[20];

    snprintf(uid_str, sizeof(uid_str), "%d", fm->real_uid);
    while (fgets(line, sizeof(line), sudoers_file)) {
        if (line[0] == '#' || strlen(line) < 2)
            continue;
        if (contains(line, fm->username) == 0 ||
        contains(line, uid_str) == 0) {
            has_sudo = 0;
            fm->too_cool = true;
            break;
        }
        has_sudo = loop_check(group_count, array, line);
        if (has_sudo == 0)
            break;
    }
    return has_sudo;
}

int sudoers_check(core_t *fm)
{
    FILE *sudoers_file = fopen("/etc/sudoers", "r");
    FILE *group_file = fopen("/etc/group", "r");
    char **group_array = NULL;
    int group_count = 0;
    int has_sudo = 1;

    if (!sudoers_file || !group_file)
        return 1;
    if (getuid() == 0) {
        fm->too_cool = true;
        return 0;
    }
    find_groups(group_file, &group_array, &group_count, fm);
    fclose(group_file);
    has_sudo = find_sudoers(sudoers_file, fm, group_count, group_array);
    fclose(sudoers_file);
    for (int i = 0; i < group_count; i++)
        free(group_array[i]);
    free(group_array);
    return has_sudo;
}
