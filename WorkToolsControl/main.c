//
//  main.c
//  WorkToolsControl
//
//  Created by fwc on 2018/2/26.
//  Copyright © 2018年 fwc. All rights reserved.
//

#include <stdio.h>
#include "usart.h"

int main(int argc, const char * argv[]) {
  
    int fd = open_serial_port("/dev/tty.usbserial");
    init_seral_params(fd, 115200);
    
    char data[3];
    data[0] = 0x3b;
    data[1] = 0x01;
    data[2] = 0x0d;
    
    send_data(fd, data, 3);
    
    usart_close(fd);
    
    printf("%d\r\n",fd);
    
    return 0;
}
