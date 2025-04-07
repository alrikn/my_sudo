/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** s_flag_handler
*/
#include "my.h"
#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
    char *shell = getenv("SHELL");
    struct passwd *pw;
    pw = getpwuid(fm->fake.fake_uid);
    if (!shell)
        shell = "/bin/sh";
    setenv("HOME", pw->pw_dir, 1);
    setenv("USER", pw->pw_name, 1);
    setenv("LOGNAME", pw->pw_name, 1);
    setenv("SHELL", shell, 1);
    setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:
    /sbin:/bin", 1);
    execlp(shell, shell, "-i", (char *)NULL);
    perror("execlp failed");
    exit(1);
*/

int copy_shell(core_t *fm)
{
    char *shell = NULL;

    strtok(NULL, ":");
    strtok(NULL, ":");
    strtok(NULL, ":");
    shell = strtok(NULL, "\n");
    if (shell)
        fm->shell = strdup(shell);
    return 0;
}

static int find_shell(core_t *fm)
{
    uid_t uid = fm->fake.fake_uid;
    FILE *passwd_file = fopen("/etc/passwd", "r");
    char *uid_str = NULL;
    char *line = NULL;
    size_t len = 0;

    if (passwd_file == NULL)
        return 1;
    while (getline(&line, &len, passwd_file) != -1) {
        strtok(line, ":");
        strtok(NULL, ":");
        uid_str = strtok(NULL, ":");
        if (uid_str != NULL && atoi(uid_str) == uid)
            return copy_shell(fm);
    }
    fclose(passwd_file);
    free(line);
    return 1;
}

int parse_env(core_t *fm)
{
    int i = 0;
    char *shell = NULL;

    while (contains(fm->env_array[i], "SHELL=")) {
        i++;
    }
    strtok(fm->env_array[i], "=");
    shell = strtok(NULL, "\n");
    if (shell) {
        fm->shell = strdup(shell);
        return 0;
    }
    return 1;
}

int s_flag_handler(core_t *fm, char **argv, int *start, int end)
{
    if (parse_env(fm) != 0)
        find_shell(fm);
    if (fm->shell != NULL)
        execlp(fm->shell, fm->shell, "-i", NULL);
    else {
        free(fm->username);
        free_array(fm->env_array);
        execlp("/bin/sh", "/bin/sh", "-i", NULL);
    }
    return 0;
}
