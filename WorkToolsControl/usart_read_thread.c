//
//  usart_read_thread.c
//  WorkToolsControl
//
//  Created by fwc on 2018/2/27.
//  Copyright © 2018年 fwc. All rights reserved.
//

#include "usart_read_thread.h"
#include "usart.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void *thread_read(void *args)
{
    int read_len;
    char buff[100];
    
    int fd = open_serial_port("/dev/ttyUSB0");
    init_seral_params(fd, 115200);
    
    printf("thread fd = %d \r\n",fd);
    
    while(1)
    {
        memset(buff,0,sizeof(char)*100);
        read_len = usart_read(fd, buff, 100);
        
        if(read_len > 0)
        {
            printf("rece data = %s ----- len = %d \r\n",buff,read_len);
        }
       
    }
    return (void*)NULL;
}
