#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include <unistd.h> 


#include <pthread.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include "clist.h"
#include "net.h"
#include "thdpool.h"
#include "terminal.h"

#define       U32TOU8(s,b)    ((s>>(b*8))&0xff)


extern int  net_tcpserver_thread();
extern void gd_client_monitor_init();
static void main_loop()
{
    while(1)
        {
            sleep(5);
        }


}


/*
*
*  arg1: client struct input
*  arg2: thread memory,config at common.h
*
*
*
*
*/
static void net_event_manage(ds_client_content* pdcc, Uint8* pmem)   
{
    
    Int32 len = 0;

    while(1){

        len = recv(pdcc->connectfd,pmem,1024,MSG_WAITFORONE);
        if(len<=0){
            printf("recv 0\n");
            goto nem_close;
        }
        if(NULL==pdcc){

            printf("can not find node \n");
            goto nem_out;
        }
        printf("recv from:%d.%d.%d.%d \n",U32TOU8(pdcc->ip,0),U32TOU8(pdcc->ip,1),U32TOU8(pdcc->ip,2),U32TOU8(pdcc->ip,3));
        printf("     %s \n",pmem);
        if(0==strncmp((char*)pmem,"close",5)){
nem_close:
            printf("client close \n");
            send(pdcc->connectfd,"link is ready close \n",21,O_NONBLOCK);

            pdcc->state = um_dead;
            goto nem_out;
        }

        //pdcc->join_listen_queue(pdcc->connectfd);
        goto nem_out;    
    }

nem_out:  
    return;
}

extern void __net_event_manage(ds_client_content* pdcc, unsigned char * pmem);
int main()
{

    pthread_t ptd;
    tdpl_pool_init();


	  //net_server_init(net_event_manage);
		net_server_init(__net_event_manage);
    
    pthread_create(&ptd,NULL,message_thread,NULL);

    gd_client_monitor_init();
    
    main_loop();

    return 0;

    
}


