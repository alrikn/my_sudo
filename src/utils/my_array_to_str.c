/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** my_array_to_str
*/

#include <stdlib.h>
#include <string.h>

static int my_strlen(char *str)
{
    char *str_end = str;

    for (; *str_end; ++str_end);
    return (str_end - str);
}

static char *my_strcat(char *dest, char const *str)
{
    char *dest_start = dest;

    if (!dest || !str)
        return NULL;
    while (*dest != '\0') {
        dest++;
    }
    while (*str != '\0') {
        *dest = *str;
        dest++;
        str++;
    }
    *dest = '\0';
    return dest_start;
}

char *array_to_phrase(char **arr, int start, int end)
{
    long total_length = 0;
    char *result = NULL;

    for (int i = start; i < end; i++) {
        total_length += my_strlen(arr[i]) + 1;
    }
    result = malloc(total_length * sizeof(char));
    if (result == NULL)
        return NULL;
    result[0] = '\0';
    for (int i = start; i < end; i++) {
        my_strcat(result, arr[i]);
        if (i < end - 1) {
            my_strcat(result, " ");
        }
    }
    return result;
}
