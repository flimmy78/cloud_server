#pragma once
#ifndef __OSA_STRING_H__
#define __OSA_STRING_H__


/*
 * Created by Liu Papillon, on Oct 12, 2017.
 */

#include <string.h>
#include "osa_primary_types.h"


#define OSA_clear(p)                                (memset((p), 0, sizeof(*p)))
#define OSA_strncpy(dst, src)                       (strncpy(dst, src, sizeof(dst)))
#define OSA_strncat(dst, src)                       (strncat(dst, src, sizeof(dst) - (sizeof((dst)[0]) * (strlen(dst) + 1))))
#define OSA_strIsEmpty(str)                         (NULL == (str) || 0 == strlen(str))



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


Bool OSA_strIsEmptyOrWhitespace(const Char *pStr);

int OSA_strTrim(const Char *src, Char *dest, Uint32 length);



#ifdef __cplusplus
}
#endif // __cplusplus


#endif  /* __OSA_STRING_H__ */

