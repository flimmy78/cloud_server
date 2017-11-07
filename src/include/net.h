/*
 *  All rights reserved. HangZhou Dongshengdianzi 
 *
 *
 * TCP server.  epoll , we do not dealing with actual business here
 * 
 *
 * Author: Jerry.Deng
 * Denghongjie@hzdusun.com
 * Date  : 2017/10/20
 *
 */


#ifndef DS_NET_H
#define DS_NET_H


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<stdbool.h>
#include "../common.h"
#include "clist.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus





typedef struct ds_net_clientinfo_t
{
    Int32   cfd;
    Uint32 ip;
    Uint32  port;
    
    
}ds_net_clientinfo;


typedef void  (*user_main)(ds_client_content*,Uint8*);


int net_server_init(user_main func);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif
