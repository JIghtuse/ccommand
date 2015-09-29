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

static inline void *xrealloc(void *pold, const size_t size)
{
    void *p = realloc(pold, size);
    if (!p && size) {
        fprintf(stderr, "cannot allocate %zu bytes\n", size);
		exit(EXIT_FAILURE);
    }
    return p;
}

static inline char *xstrdup(const char *str)
{
    char *ret;
    if (!str)
        return NULL;

    ret = strdup(str);
    if (!ret) {
        fprintf(stderr, "cannot duplicate strig\n");
		exit(EXIT_FAILURE);
    }

    return ret;
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
