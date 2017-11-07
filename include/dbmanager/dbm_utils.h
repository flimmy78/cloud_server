#pragma once
#ifndef __DBM_UTILS_H__
#define __DBM_UTILS_H__

#include <osa/osa.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	Char* DBM_utlGenUuid(Char *pUuid, const size_t bufferLength);

    inline int DBM_utlIsUuidValid(const Char *pUuid)
    {
        return NULL != pUuid && strlen(pUuid) == 32;  /* '-' is stripped */
    }

    inline int DBM_utlIsDateTimeValid(const Char *pDatetime)
    {
        return NULL != pDatetime && strlen(pDatetime) > 0;
    }
    	

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  /* __DBM_UTILS_H__ */
