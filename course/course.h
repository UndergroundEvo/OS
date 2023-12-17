#ifndef COURSE
#define COURSE

#include<netinet/in.h>
#include<errno.h>
#include<netdb.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/ip_icmp.h>
#include<netinet/udp.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

FILE *logfile; //место для вывода данных
struct sockaddr_in source, dest; //cтруктуры для хранения IP-адресов отправителя и получателя
int tcp = 0, udp = 0, others = 0, total = 0, i, j; //подсчет пакетов

void ProcessPacket(unsigned char *, int); //обработка пакета, выбор функции для обработки
void print_ip_header(unsigned char *, int); //вывод заголовка ip
void print_tcp_packet(unsigned char *, int); //вывод содержимого TCP пакета
void print_udp_packet(unsigned char *, int); //вывод содержимого UDP пакета
void PrintData(unsigned char *, int); // вывод RAW данных
void DaemonMode(); //Основная функция программы
#endif