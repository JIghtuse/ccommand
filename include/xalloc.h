#ifndef _CCOMMAND_XALLOC_H_
#define _CCOMMAND_XALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline char *xstrdup(const char *str)
{
    if (!str)
        return NULL;

    return strdup(str);
}

static inline int vxasprintf(char **strp, const char *fmt, va_list argp)
{
    int ret;
    ret = vasprintf(strp, fmt, argp);
    if (ret < 0) {
        fprintf(stderr, "cannot allocate a string\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _CCOMMAND_XALLOC_H_
