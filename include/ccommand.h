#ifndef _CCOMMAND_CCOMMAND_H_
#define _CCOMMAND_CCOMMAND_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

struct ccommand {
    const char **args;
    size_t nargs;
};

int ccommand_init(struct ccommand *cmd, const char* program);
int ccommand_add_arg(struct ccommand *cmd, const char *fmt, ...);
int ccommand_exec(struct ccommand *cmd);
int ccommand_cleanup(struct ccommand *cmd);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _CCOMMAND_CCOMMAND_H_
