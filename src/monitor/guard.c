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
#include <stdlib.h>
#include <unistd.h>

#include "clist.h"

#define   GD_CLIENT_SUBSISTENCE_TIME                  (30*60)  /* 30 min*/

static void*  main_loop(void*)
{
    ds_client_content *client = NULL;
    struct timespec time;


    while(true){

        clock_gettime(CLOCK_REALTIME, &time);
        
        for(client = dss_get_last_client();client!=NULL;client=dss_get_next_client(client)){
            
            if((time.tv_sec - client->reflash_time) > GD_CLIENT_SUBSISTENCE_TIME){


                printf("dectect dead client \n");
                client->dequeue_listen(client->connectfd);
                close(client->connectfd);
                dss_del_client(client);
            }
        }

        sleep(GD_CLIENT_SUBSISTENCE_TIME);

    }
    return NULL;
}





void gd_client_monitor_init()
{
    pthread_t  thread;
    
    if(pthread_create(&thread,NULL,main_loop,NULL)){

        perror("new guard thread");
        return;
    }

    return;

        
    
}

