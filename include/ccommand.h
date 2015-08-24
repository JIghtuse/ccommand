#ifndef _LIB_CCOMMAND_H_
#define _LIB_CCOMMAND_H_

#ifdef __cplusplus
    extern "C" {
#endif // __cplusplus


/* Drop-in replacement for system() call */
int ccommand_exec(const char *cmd);


#ifdef __cplusplus
    }
#endif // __cplusplus

#endif // _LIB_CCOMMAND_H_
