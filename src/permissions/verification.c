/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** verification
*/

#include "my.h"
#include "struct.h"

int comparer(char *hash, char *settings, core_t *fm)
{
    char *input = NULL;

    for (int i = 0; i < 3; i++) {
        printf("[my_sudo] password for %s:", fm->username);
        input = getpass("");
        if (contains(crypt(input, settings), hash) == 0) {
            return 0;
        }
        printf("Sorry, try again.\n");
    }
    printf("my_sudo: 3 incorrect password attempts\n");
    return 1;
}

static void getting_variables(const char *last_dollar, char *settings,
    char *hash, const char *password_field)
{
    const char *hash_start = NULL;
    const char *hash_end = NULL;
    size_t hash_len = 0;
    size_t settings_len = 0;

    hash_start = last_dollar + 1;
    hash_end = strchr(hash_start, ':');
    if (!hash_end)
        return;
    hash_len = hash_end - hash_start;
    strncpy(hash, last_dollar, hash_len + 1);
    hash[hash_len + 1] = '\0';
    settings_len = last_dollar - password_field;
    strncpy(settings, password_field, settings_len);
    settings[settings_len] = '\0';
}

void parse_shadow_entry(const char *line, char *settings, char *hash)
{
    const char *password_field = strchr(line, ':');
    const char *last_dollar = NULL;

    if (!password_field)
        return;
    password_field++;
    last_dollar = strrchr(password_field, '$');
    if (!last_dollar)
        return;
    getting_variables(last_dollar, settings, hash, password_field);
}

int loop(core_t *fm, char *line)
{
    char *line_copy = NULL;
    char *username = NULL;
    char settings[MAX_BUFFER] = {0};
    char hash[MAX_BUFFER] = {0};

    line_copy = strdup(line);
    if (!line_copy)
        return 1;
    username = strtok(line, ":");
    if (username == NULL)
        free(line_copy);
    if (username != NULL && strcmp(username, fm->username) == 0) {
        parse_shadow_entry(line_copy, settings, hash);
        free(line_copy);
        free(line);
        return comparer(hash, settings, fm);
    }
    free(line_copy);
    return 2;
}

int finder(core_t *fm, FILE *shadow_file)
{
    char *line = NULL;
    size_t len = 0;
    int return_value = 2;

    while (getline(&line, &len, shadow_file) != -1) {
        return_value = loop(fm, line);
        if (return_value != 2)
            return return_value;
    }
    free(line);
    return 1;
}

int verify_password(core_t *fm)
{
    FILE *shadow_file = fopen("/etc/shadow", "r");
    int i = 0;

    if (shadow_file == NULL) {
        perror("Failed to open /etc/shadow");
        return 1;
    }
    i = finder(fm, shadow_file);
    fclose(shadow_file);
    return i;
}
