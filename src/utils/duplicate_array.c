/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** duplicate_array
*/

#include <stdlib.h>
#include <string.h>

char **arrdup(char **array)
{
    char **new;
    int len = 0;

    while (array[len] != NULL)
        len++;
    new = malloc(sizeof(char *) * len);
    for (int i = 0; i < len; i++) {
        new[i] = strdup(array[i]);
    }
    return new;
}
