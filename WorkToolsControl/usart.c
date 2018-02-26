//
//  usart.c
//  WorkToolsControl
//
//  Created by fwc on 2018/2/26.
//  Copyright © 2018年 fwc. All rights reserved.
//

#include "usart.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

int open_serial_port(const char *tty)
{
    int fd = open(tty, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1)
    {
        perror("open serial fail");
        return fd;
    }
    
    if(fcntl(fd, F_SETFL,0) < 0)
    {
        perror("fcnfl fail");
        return -1;
    }
    
    if(isatty(fd) == 0)
    {
        printf("not termios device");
        return -1;
    }
    
    return fd;
}

int init_seral_params(int fd,int speed)
{
    struct termios port_attr;
    if(tcgetattr(fd, &port_attr) != 0)
    {
        perror("get termios attr fail");
        return -1;
    }
    
    //波特率
    switch (speed) {
        case 9600:
            cfsetispeed(&port_attr, B9600);
            cfsetospeed(&port_attr, B9600);
            break;
        case 115200:
            cfsetispeed(&port_attr, B115200);
            cfsetospeed(&port_attr, B115200);
            break;
        default:
            cfsetispeed(&port_attr, B9600);
            cfsetospeed(&port_attr, B9600);
            break;
    }
    
    port_attr.c_cflag |= CLOCAL | CREAD;
    port_attr.c_cflag &= ~CRTSCTS;//不使用硬件流控制
    port_attr.c_cflag &= ~CSIZE;
    port_attr.c_cflag |= CS8;//8位数据
    port_attr.c_cflag &= ~PARENB;//无奇偶校验
    port_attr.c_iflag &= ~INPCK;
    port_attr.c_cflag &= ~CSTOPB;//停止1位
    port_attr.c_cc[VTIME] = 0;
    port_attr.c_cc[VMIN]  = 0;
    port_attr.c_oflag &= ~OPOST;//原始数据输出
    port_attr.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    
    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读
    tcflush(fd,TCIFLUSH);
    
    if(tcsetattr(fd, TCSANOW, &port_attr) != 0)
    {
        perror("init serial port fail");
        return  -1;
    }
    
    return fd;
}

void send_data(int fd,char *buff,int len)
{
    ssize_t slen = write(fd, buff, len);
    
    if(slen == len)
    {
        printf("send data success");
    }
    else
    {
        tcflush(fd,TCOFLUSH);
        perror("write fail");
    }
    
}

void usart_close(const int fd)
{
    close(fd);
}

