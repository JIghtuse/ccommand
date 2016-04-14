#include <ccommand.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static inline char *xstrdup(const char *str)
{
    if (!str)
        return NULL;

    return strdup(str);
}

static int increase_capacity(struct ccommand *cmd)
{
    size_t new_capacity = cmd->capacity ? cmd->capacity * 2 : 1;
    size_t new_size = new_capacity * sizeof(char*);
    const char **new_args = realloc((char**)cmd->args, new_size);
    if (new_args == NULL)
        return -1;
    cmd->args = new_args;
    cmd->capacity = new_capacity;
    return 0;
}

static int ccommand_add_arg_private(struct ccommand *cmd, const char *arg)
{
    if (cmd->capacity <= cmd->nargs && increase_capacity(cmd) < 0) {
        return -1;
    }
    int idx = cmd->nargs++;
    cmd->args[idx] = xstrdup(arg);
    if (arg && !cmd->args[idx])
        return -1;
    return 0;
}

int ccommand_init(struct ccommand *cmd, const char *program)
{
    if (!cmd || !program)
        return -1;

    cmd->args = NULL;
    cmd->nargs = 0;
    cmd->capacity = 0;
    return ccommand_add_arg_private(cmd, program);
}

int ccommand_add_arg(struct ccommand *cmd, const char *fmt, ...)
{
    if (!cmd || !fmt)
        return -1;

    char *arg_str;
    va_list argp;
    int ret;

    va_start(argp, fmt);
    ret = vasprintf(&arg_str, fmt, argp);
    va_end(argp);
    
    if (ret == -1)
        return -1;

    ret = ccommand_add_arg_private(cmd, arg_str);

    free(arg_str);
    return ret;
}

int ccommand_exec(struct ccommand *cmd)
{
    if (!cmd || !cmd->args || cmd->nargs == 0)
        return -1;

    if (ccommand_add_arg_private(cmd, NULL) < 0)
        return -1;

    int status;
    pid_t child_pid;
    switch (child_pid = fork()) {
    case -1:
        return -1;
    case 0:
        execvp(cmd->args[0], (char * const *)cmd->args);
        abort();
    default:
        do {
            if (waitpid(child_pid, &status, 0) == -1) {
                return -1;
            } else if (WIFEXITED(status)) {
                return WEXITSTATUS(status);
            } else {
                return -1;
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int ccommand_cleanup(struct ccommand *cmd)
{
    if (!cmd || !cmd->args)
        return 0;

    for (size_t i = 0; i < cmd->nargs; i++) {
        free((char*)cmd->args[i]);
    }

    free(cmd->args);
    cmd->args = NULL;
    cmd->nargs = 0;
    cmd->capacity = 0;
    return 0;
}
