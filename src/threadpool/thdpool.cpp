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

#include "thdpool.h"
#include "threadpool.hpp"

using namespace std;
using namespace boost::threadpool;


pool_ptr  gthread_pool_ptr;


Int32 tdpl_pool_init()
{
    gthread_pool_ptr = new pool(DS_THDPOOL_DEEP);
    if(NULL==gthread_pool_ptr)
        return -1;
    return 0;
}

void tdpl_pool_dinit()
{
    delete gthread_pool_ptr;
}


void tdpl_pool_wait()
{
    gthread_pool_ptr->wait();
}



Int32 tdpl_pool_push(tdpl_task_info* ptaskinfo)
{
    
    if(NULL!=ptaskinfo)
        return  gthread_pool_ptr->schedule((tdpl_task_info*)ptaskinfo);
    return false;
}






#if 0

void first_task(void *p1,void* p2)
{
    cout << "first task is running\n" ;
    printf("%s  %#x \n",p1,p2);
}
int main(void)
{

    // Create fifo thread pool container with two threads.
   // pool tp(1);
   
    tdpl_task_info tti;
    char aa[]="chengyongfei da sha bi \n";


    tti.func = first_task;
    tti.argc = (void*)aa;

    tdpl_pool_init();

    tdpl_pool_push(&tti);

    while(1){sleep(5);}
    // Now all tasks are finished!    
    return(0);

}


#endif 


