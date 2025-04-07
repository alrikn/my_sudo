/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** free_array
*/

#include <stdlib.h>

void free_array(char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        free(array[i]);
    }
}
