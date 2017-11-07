/*
 *  All rights reserved. HangZhou Dongshengdianzi 
 *
 *
 * This profile is for TCP Server setting
 *
 * Author: Jerry.Deng
 * Denghongjie@hzdusun.com
 *
 */
     
#ifndef DS_NET_COMMON_H
#define DS_NET_COMMON_H


#include "../include/osa_primary_types.h"



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/*
*
*  Server configration
*   
*/
/* TCP listening port  */
#define  DS_TCPLISTEN_PORT          8989

/* thread pool deep  */
#define DS_THDPOOL_DEEP             (20)

/* epoll get events max */
#define  DS_TCPEVENTS_MAX           (DS_THDPOOL_DEEP<<2)

/* tcp listening port number */
#define  DS_TCPLISTEN_MAX           (DS_THDPOOL_DEEP)







#ifdef __cplusplus
}
#endif // __cplusplus



#endif
