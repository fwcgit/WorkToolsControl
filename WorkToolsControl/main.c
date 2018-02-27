//
//  main.c
//  WorkToolsControl
//
//  Created by fwc on 2018/2/26.
//  Copyright © 2018年 fwc. All rights reserved.
//

#include <stdio.h>
#include "usart.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
  
    int fd = open_serial_port("/dev/ttyUSB0");
    init_seral_params(fd, 115200);
    char data[3];
    char *input = (char*)malloc(sizeof(char)*10);
    
    while(1)
    {
        gets(input);
        if(strstr(input, "off"))
        {
            data[0] = 0x3b;
            data[1] = 0x00;
            data[2] = 0x0d;
            send_data(fd, data, 3);
        }
        else if(strstr(input, "on"))
        {
            data[0] = 0x3b;
            data[1] = 0x01;
            data[2] = 0x0d;
            send_data(fd, data, 3);
        }
        else if(strstr(input, "exit"))
        {
            usart_close(fd);
            break;
        }
    }
    
    printf("%d\r\n",fd);
    
    return 0;
}
