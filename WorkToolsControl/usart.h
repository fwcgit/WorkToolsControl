//
//  usart.h
//  WorkToolsControl
//
//  Created by fwc on 2018/2/26.
//  Copyright © 2018年 fwc. All rights reserved.
//

#ifndef usart_h
#define usart_h

int open_serial_port(const char *tty);
int init_seral_params(int fd,int speed);
void send_data(int fd,char *buff,int len);
void usart_close(const int fd);
int  usart_read(int fd,char *buff,int len);
void usart_thread();

#endif /* usart_h */
