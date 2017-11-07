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

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/epoll.h>


#include "net.h"
#include "clist.h"
#include "thdpool.h"



#define       U32TOU8(s,b)    ((s>>(b*8))&0xff)



/* global variable */

Int32         gEpollfd;
user_main     usr_main = NULL;


static void net_event__process(void* arg1,void*arg2);





static void eventpoll_add(Int32 sockfd)
{
    struct epoll_event ev;
    
    ev.events = (EPOLLIN | EPOLLET);
    ev.data.fd = sockfd;
    if(-1==epoll_ctl(gEpollfd,EPOLL_CTL_ADD,sockfd,&ev)){
            
        perror("epoll_ctl");
    }
    return;
}

static void eventpoll_delete(Int32 sockfd)
{
    struct epoll_event ev;
    
    ev.events = (EPOLLIN | EPOLLET);
    ev.data.fd = sockfd;
    
    if(-1==epoll_ctl(gEpollfd,EPOLL_CTL_DEL,sockfd,&ev)){
            
        perror("epoll_ctl");
    }
    return;
}


static Int32  net_tcpserver_create()
{
    Int32 sock;
    struct sockaddr_in svr_addr;


    
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)  
    {    
        perror("socket");  
        return -1;  
    }

    
    memset(&svr_addr, 0 , sizeof(svr_addr));
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = htons(INADDR_ANY);
    svr_addr.sin_port = htons(DS_TCPLISTEN_PORT);

    if(bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr))<0){

        printf("bind failed \n");
        return -1;
    }

    listen(sock, DS_TCPLISTEN_MAX);

    return sock;
    
}



static Int32  net_tcpserver_getclient(Int32 fd, ds_net_clientinfo* cinfo)
{
        Uint32 size;
        struct sockaddr_in  cli_addr;
        Int32 linkfd;
        
        size = sizeof(cli_addr);
        
        linkfd = accept(fd,(struct sockaddr*)(&cli_addr), &size);
        if(linkfd<0){
            
            printf("%s-%d : error \n",__func__,__LINE__);
            return -1;

        }

        cinfo->cfd = linkfd;
        cinfo->ip = cli_addr.sin_addr.s_addr;
        cinfo->port = ntohs(cli_addr.sin_port);
        return 0;

}


static ds_client_content *new_client(ds_net_clientinfo *pcinfo)
{

    ds_client_content* pcc;

    pcc  = dss_add_client();
    if(NULL==pcc)
        return pcc;
    
    pcc->func = net_event__process;
    pcc->self = pcc;
    pcc->enqueue_listen = eventpoll_add;
    pcc->dequeue_listen = eventpoll_delete;
    pcc->connectfd = pcinfo->cfd;
    pcc->ip = pcinfo->ip;
    pcc->port = pcinfo->port;
    pcc->state = um_ready;
    return pcc;
}

static void eventpoll_init(struct epoll_event **pevents)
{

    *pevents = (struct epoll_event*)malloc((sizeof(struct epoll_event))*DS_TCPEVENTS_MAX);
    
    if(NULL==*pevents)
        printf("%s-%d error \n",__func__,__LINE__);

    return;
}


static void*  net_tcpserver_thread(void*)
{
    Int32 sock;
    ds_net_clientinfo cinfo;

    struct epoll_event ev;
    struct epoll_event *pevents = NULL;
    //Int32 epollfd;
    Int32 eventcnt,n;
    ds_client_content* pcc;

    
    sock = net_tcpserver_create();
    if(sock<0){
        
        return NULL;
    }

    eventpoll_init(&pevents);
    if(NULL==pevents)
        return NULL;

    gEpollfd = epoll_create(DS_TCPEVENTS_MAX);
    if(gEpollfd<0){

        perror("epoll_create");
        return NULL;
    }
        
    ev.events = EPOLLIN;
    ev.data.fd = sock;
    if(-1==epoll_ctl(gEpollfd,EPOLL_CTL_ADD,sock,&ev)){
            
        perror("epoll_ctl");
        goto ntt_error;
    }
    while(true){
        
        eventcnt = epoll_wait(gEpollfd,pevents,DS_TCPEVENTS_MAX,-1); 
        if(-1==eventcnt){
            perror("epoll_wait");
            goto ntt_error;
        }
        for(n=0;n<eventcnt;n++){
            
            if(sock==pevents[n].data.fd){
                net_tcpserver_getclient(sock,&cinfo);
                if(dss_find_client_ip(cinfo.ip)){
                    printf("This IP is connected \n");
                    continue;
                }
                                
                pcc = new_client(&cinfo);
                if(NULL==pcc)
                    continue;
                //dss_add_client(pcc);
                pcc->state = um_running;
                pcc->parent_fd = gEpollfd;
                eventpoll_add(pcc->connectfd);
            }
            else if(EPOLLIN&pevents[n].events){

                pcc = dss_find_client_fd(pevents[n].data.fd);
                if(NULL!=pcc){
                    
                    eventpoll_delete(pevents[n].data.fd);
                    tdpl_pool_push((tdpl_task_info* )pcc);
                }
                else{
                    /* remove from epoll */
                    eventpoll_delete(pevents[n].data.fd);
                }
                
            }
            
            else if((EPOLLERR|EPOLLHUP)&pevents[n].events){
                   eventpoll_delete(pevents[n].data.fd);
                   pcc = dss_find_client_fd(pevents[n].data.fd);
                   if(NULL!=pcc){
                       dss_del_client(pcc);
                       pcc = NULL;
                   }
                   
            }
                
        }

    }
        

ntt_error:
        close(sock);
        if(NULL!=pevents)
            free(pevents);
        
        return NULL;
    
}






static void net_event__process(void* arg1,void*arg2)
{
    ds_client_content* pdcc = (ds_client_content*)arg1;
    Uint8* pmem = (Uint8*)arg2;
    struct timespec time;

    clock_gettime(CLOCK_REALTIME, &time);
    pdcc->reflash_time = time.tv_sec;
    usr_main(pdcc,pmem);

    if(um_dead==pdcc->state){
        close(pdcc->connectfd);
        dss_del_client(pdcc);
        return;
    }
    
    pdcc->enqueue_listen(pdcc->connectfd);
     
}



int net_server_init(user_main func)
{
    pthread_t  thread;
    
    if(NULL==func)
        printf("%s-%d: error \n",__func__,__LINE__);

    usr_main = func;

    
    if(pthread_create(&thread,NULL,net_tcpserver_thread,NULL)){

        perror("new server thread");
        return -1;
    }

    return 1;
}





/***************************************************************************************************************
    
                      

***************************************************************************************************************/


