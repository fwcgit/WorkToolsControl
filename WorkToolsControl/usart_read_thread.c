//
//  usart_read_thread.c
//  WorkToolsControl
//
//  Created by fwc on 2018/2/27.
//  Copyright © 2018年 fwc. All rights reserved.
//

#include "usart_read_thread.h"
#include "usart.h"
void *thread_read(void *args)
{
    printf("thread fd = %d \r\n",*((int *)args));
    
    while(1)
    {
        int read_len;
        char buff[100];
        read_len = usart_read(*((int*)args), buff, 100);
        
        if(read_len > 0)
        {
            printf("rece data = %s ----- len = %d \n",buff,read_len);
        }
       
    }
    return (void*)NULL;
}
