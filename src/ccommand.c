#include <ccommand.h>
#include <xalloc.h>

#include <stdlib.h>

static void ccommand_add_arg_private(struct ccommand *cmd, const char *arg)
{
    size_t new_size = (cmd->nargs + 1) * sizeof(char*);
    cmd->args = xrealloc((char**)cmd->args, new_size);
    cmd->args[cmd->nargs++] = xstrdup(arg);
}

int ccommand_init(struct ccommand *cmd, const char *program)
{
    if (!cmd || !program)
        return -1;

    cmd->nargs = 0;
    ccommand_add_arg_private(cmd, program);
    return 0;
}

int ccommand_add_arg_cstr(struct ccommand *cmd, const char *arg)
{
    if (!cmd || !arg)
        return -1;
    ccommand_add_arg_private(cmd, arg);
    return 0;
}

int ccommand_add_arg_int(struct ccommand *cmd, int arg)
{
    if (!cmd)
        return -1;
    char *arg_str;
    xasprintf(&arg_str, "%d", arg);
    ccommand_add_arg_private(cmd, arg_str);
    free(arg_str);
    return 0;
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
    return 0;
}
