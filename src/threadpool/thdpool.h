/*
 *  All rights reserved. HangZhou Dongshengdianzi 
 *
 *
 * TCP server thread pool.
 * 
 *
 * Author: Jerry.Deng
 * Denghongjie@hzdusun.com
 * Date  : 2017/10/20
 *
 */


#ifndef DS_THDPOOL_H
#define DS_THDPOOL_H


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../common.h"




#ifdef __cplusplus
extern "C" {
#endif // __cplusplus




typedef  struct tdpl_task_info_t* ptdpl_task_info;
typedef struct tdpl_task_info_t{

    /* 
    *  
    *  argc1: user input. 
    *  argc2: memory auto alloc by thread pool.Memory size define by  WORKSPACE_MEM 
    */
    void   (*func)(void*,void*);
    void*    argc;

}tdpl_task_info;





Int32 tdpl_pool_init();

void tdpl_pool_dinit();

void tdpl_pool_wait();


Int32 tdpl_pool_push(tdpl_task_info* ptaskinfo);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif
