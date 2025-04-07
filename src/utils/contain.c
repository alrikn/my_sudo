/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** contain
*/

#include <stdio.h>
#include <string.h>

static int my_strlen(char const *str)
{
    char const *ptr = str;
    int len = 0;

    if (!str)
        return 0;
    while (*ptr != '\0') {
        ptr++;
        len++;
    }
    return (len);
}

int contains(const char *big, const char *small)
{
    size_t big_len = my_strlen(big);
    size_t small_len = my_strlen(small);

    if (!big || !small)
        return 1;
    if (small_len > big_len) {
        return 1;
    }
    for (size_t i = 0; i <= big_len - small_len; i++) {
        if (strncmp(&big[i], small, small_len) == 0) {
            return 0;
        }
    }
    return 1;
}
