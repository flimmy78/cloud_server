/*
 *  All rights reserved. HangZhou Dongshengdianzi 
 *
 *
 * TCP server monitor/message 
 * 
 *
 * Author: Jerry.Deng
 * Denghongjie@hzdusun.com
 * Date  : 2017/10/20
 *
 */


#ifndef DS_MESSAGE_H
#define DS_MESSAGE_H


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <fcntl.h>  
#include <limits.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>


#include <sys/socket.h>
#include <sys/un.h>
#include "../common.h"




void  *message_thread(void*);



#ifdef __cplusplus
}
#endif // __cplusplus


#endif

