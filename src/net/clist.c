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



#include "clist.h"
#include <string.h>



#define INFO(format) fprintf(stderr,"%s:%d:%s -> " format "\n", __FILE__, __LINE__, __func__)


#undef offsetof  
#ifdef __compiler_offsetof  
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)  
#else  
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)  
#endif  
#define ds_container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})




static pthread_mutex_t g_Mutex = PTHREAD_MUTEX_INITIALIZER ;

typedef struct  ds_client_node_t ds_client_node;
    
struct  ds_client_node_t
{
    ds_client_node      *pre;
    ds_client_content    cn;
    ds_client_node      *next;
};


ds_client_node*  glastnode = NULL;


static time_t  getmytime()
{
    struct timespec time;

    clock_gettime(CLOCK_REALTIME, &time); 
    return time.tv_sec; /* get time from 1970  */
    
}
static void  _add(ds_client_node* cnd)
{
    
    if(NULL==glastnode){
        glastnode = cnd;
    }

    else{
        glastnode->next = cnd;
        cnd->pre = glastnode;
        glastnode = cnd;
    }
}


static void  _delete(ds_client_node* cnd)
{

    ds_client_node *pre = NULL;
    ds_client_node *next = NULL;

    pre = cnd->pre;
    next = cnd->next;

    if(NULL!=pre)
    pre->next = next;
    if(NULL!=next)
    next->pre = pre;

    if(cnd==glastnode)
        glastnode = pre;
    
}


static ds_client_node*  _find(ds_client_content* cn)
{

    if(NULL==cn)
    return NULL;

    return (ds_client_node*)(ds_container_of(cn,ds_client_node,cn));
}



ds_client_content*  dss_add_client()
{
    ds_client_node *node;

    node = (ds_client_node*)malloc(sizeof(ds_client_node));
    if(NULL==node){
        INFO("malloc failed \n");
        return NULL;
    }
    memset(node,0,sizeof(ds_client_node));
    
    /* Init time param  here */
    node->cn.login_time = getmytime();
    node->cn.reflash_time = node->cn.login_time;

    pthread_mutex_lock(&g_Mutex);
    _add(node);
    pthread_mutex_unlock(&g_Mutex);
    return &(node->cn);
    
}


Int32 dss_del_client(ds_client_content* cn)
{
    ds_client_node *node;
    
    if(NULL==cn){
        INFO("input error");
        return -1;
    }
    pthread_mutex_lock(&g_Mutex);
    node = _find(cn);
    if(NULL==node){

        INFO("can not find node");
        goto del_error;
    }
    _delete(node);
    pthread_mutex_unlock(&g_Mutex);
    free(node);
    return 0;
del_error:
    pthread_mutex_unlock(&g_Mutex);
    return -1;
    
}


ds_client_content *dss_find_client_ip(Uint32 ip)
{    
    ds_client_node* cur;

    for(cur=glastnode;NULL!=cur;cur=cur->pre)
    {
        if(ip==cur->cn.ip)
            return &(cur->cn);
    }

    return NULL;
    
}


ds_client_content *dss_find_client_fd(Int32 fd)
{    
    ds_client_node* cur;

    for(cur=glastnode;NULL!=cur;cur=cur->pre)
    {
        if(fd==cur->cn.connectfd)
            return &(cur->cn);
    }

    return NULL;
    
}


ds_client_content* dss_get_last_client()
{
    ds_client_node *pnode = NULL;
    pnode = glastnode;

    return (pnode==NULL)?(NULL):(&(pnode->cn));
    
}


ds_client_content* dss_get_next_client(ds_client_content* preclient)
{
    ds_client_node *pnode = NULL;
    if(NULL!=preclient)

    pnode =  ds_container_of(preclient,struct ds_client_node_t,cn);
    pnode = pnode->next;
    return (pnode==NULL)?(NULL):(&(pnode->cn));

    
}



