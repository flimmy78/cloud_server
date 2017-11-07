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


#include "terminal.h"
#include <stdlib.h>
#include "clist.h"


#define FIFO_NAME "/var/tmp/server"  
#define BUFFER_SIZE (1024)  


#define       U32TOU8(s,b)    ((s>>(b*8))&0xff)

static inline  bool command_match(Int8 *s,Int8* cmd)
{
    return strncmp(s,cmd,sizeof(s));
}


void  message_handle(Int8* cmd)
{
    ds_client_content *client = NULL;
    
    
    if(command_match("list",cmd)){

        for(client = dss_get_last_client();client!=NULL;client=dss_get_next_client(client)){
            
              printf("%d.%d.%d.%d\n",U32TOU8(client->ip,0),U32TOU8(client->ip,1),U32TOU8(client->ip,2),U32TOU8(client->ip,3));
        }
            
    }
        
    
}


void* message_thread(void*)  
{  
    Int32 pipe_fd;  
    Int32 res;  
    Int8 buffer[BUFFER_SIZE];  

    mkfifo(FIFO_NAME, 0777); 
    memset(buffer, '\0', sizeof(buffer));  
  
    pipe_fd = open(FIFO_NAME, O_RDONLY);  

    if (pipe_fd<0){  
        
        exit(EXIT_FAILURE); 
    }  
    while(true){

        memset(buffer,0,BUFFER_SIZE);
        res = read(pipe_fd, buffer, BUFFER_SIZE);
        if(res>0)
            message_handle(buffer);
    }
     

    close(pipe_fd);  
    exit(EXIT_SUCCESS);  
}

