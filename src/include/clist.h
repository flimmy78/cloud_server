/*
 *  All rights reserved. HangZhou Dongshengdianzi 
 *
 *
 * This program is design for Client list Operating.
 * you can add client information here.
 *
 * Author: Jerry.Deng
 * Denghongjie@hzdusun.com
 * Date  : 2017/10/20
 *
 */


#ifndef DS_CLIST_H
#define DS_CLIST_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../common.h"



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


typedef enum clientState{

      um_ready,
      um_running,
      um_dead
    
}clientState;


/*  the   1th&2th element must be fuc and self */

typedef struct ds_client_content_t
{
    void (*func)(void*,void*);    /* thread pool use */
    void*               self;     /* here store herself */
    void (*enqueue_listen)(int);          /* call this func after corporation */
    void (*dequeue_listen)(int);
    Uint32              ip;
    Int32               port;
    Int32               connectfd;
    Int32               parent_fd;
    time_t              login_time;  /* second */
    time_t              reflash_time; /* second */
    clientState         state;
    
}ds_client_content;

ds_client_content* dss_add_client(void);
Int32 dss_del_client(ds_client_content* cn);




/* 
*  func:   find ip connected
*  input:  ip
*  return: 1:found 0:not found
*/

ds_client_content *dss_find_client_ip(Uint32 ip);
ds_client_content *dss_find_client_fd(Int32 fd);



ds_client_content* dss_get_last_client(void);
ds_client_content* dss_get_next_client(ds_client_content* preclient);





#ifdef __cplusplus
}
#endif // __cplusplus




#endif
