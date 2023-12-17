#include "course.h"

void ProcessPacket(unsigned char *buffer, int size) { //Получаем заголовок пакета, выбираем как обработать
    struct iphdr *iph = (struct iphdr *) (buffer + sizeof(struct ethhdr));
    ++total;
    switch (iph->protocol){ //Выбираем протокол
        case 6:  //TCP
            ++tcp;
            print_tcp_packet(buffer, size);
            break;
        case 17: //UDP
            ++udp;
            print_udp_packet(buffer, size);
            break;
        default: //Другие
            ++others;
            break;
    }
    if (logfile != stdout) printf("TCP : %d   UDP : %d   Другие : %d   Всего : %d\r", tcp, udp, others, total);
}
void print_ethernet_header(unsigned char *Buffer, int Size) {
    struct ethhdr *eth = (struct ethhdr *) Buffer; //достаем из буфера в ethhdr структуру
    time_t realtime = time(NULL);

    fprintf(logfile, "\nЗаголовок интернет пакета\n");
    fprintf(logfile, "  Время получения   - %s",  asctime(gmtime(&realtime)));
    fprintf(logfile, "  Адрес получателя  - %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0], eth->h_dest[1],
            eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
    fprintf(logfile, "  Адрес отправителя - %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0], eth->h_source[1],
            eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
    fprintf(logfile, "  Протокол          - %u \n", (unsigned short) eth->h_proto);
}
void print_ip_header(unsigned char *Buffer, int Size) {
    print_ethernet_header(Buffer, Size);
    unsigned short iphdrlen;
    struct iphdr *iph = (struct iphdr *) (Buffer + sizeof(struct ethhdr));

    /*
     struct iphdr {
    #if defined(__LITTLE_ENDIAN_BITFIELD)
	uint8_t  ihl    :4,
		 version:4;
    #elif defined (__BIG_ENDIAN_BITFIELD)
	uint8_t  version:4,
  		 ihl    :4;
    #else
    #error	"Please fix <asm/byteorder.h>"
    #endif
	uint8_t	  tos;
	uint16_t  tot_len;
	uint16_t  id;
	uint16_t  frag_off;
	uint8_t   ttl;
	uint8_t   protocol;
	uint16_t  check;
	int32_t   saddr;
	int32_t   daddr;
    };
     */

    iphdrlen = iph->ihl * 4;
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;

    fprintf(logfile, "\n");
    fprintf(logfile, "IP Заголовок\n");
    fprintf(logfile, "  Версия IP протокола          - IPv%d\n", (unsigned int) iph->version);
    fprintf(logfile, "  Длинна IP заголовка          - %d Байт\n",((unsigned int) (iph->ihl)) * 4);
    fprintf(logfile, "  Тип сервиса                  - %d\n", (unsigned int) iph->tos);
    fprintf(logfile, "  Полная длинна заголовка IP   - %d Байт\n", ntohs(iph->tot_len));
    fprintf(logfile, "  Индификатор                  - %d\n", ntohs(iph->id));
    fprintf(logfile, "  TTL                          - %d\n", (unsigned int) iph->ttl);
    fprintf(logfile, "  Протокол                     - %d\n", (unsigned int) iph->protocol);
    fprintf(logfile, "  Чексумма                     - %d\n", ntohs(iph->check));
    fprintf(logfile, "  IP Отправителя               - %s\n", inet_ntoa(source.sin_addr));
    fprintf(logfile, "  IP Назначения                - %s\n", inet_ntoa(dest.sin_addr));
}
void print_tcp_packet(unsigned char *Buffer, int Size) {
    unsigned short iphdrlen;
    struct iphdr *iph = (struct iphdr *) (Buffer + sizeof(struct ethhdr));
    iphdrlen = iph->ihl * 4;

    /*
    struct tcphdr {
	__be16	source;
	__be16	dest;
	__be32	seq;
	__be32	ack_seq;
    #if defined(__LITTLE_ENDIAN_BITFIELD)
	__u16	res1:4,
		doff:4,
		fin:1,
		syn:1,
		rst:1,
		psh:1,
		ack:1,
		urg:1,
		ece:1,
		cwr:1;
    #elif defined(__BIG_ENDIAN_BITFIELD)
	__u16	doff:4,
		res1:4,
		cwr:1,
		ece:1,
		urg:1,
		ack:1,
		psh:1,
		rst:1,
		syn:1,
		fin:1;
    #else
    #error	"Adjust your <asm/byteorder.h> defines"
    #endif
	__be16	window;
	__sum16	check;
	__be16	urg_ptr;
    };
     */

    struct tcphdr *tcph = (struct tcphdr *) (Buffer + iphdrlen + sizeof(struct ethhdr));
    int header_size = sizeof(struct ethhdr) + iphdrlen + tcph->doff * 4;

    fprintf(logfile, "\n-----------------------------------------------------------");

    fprintf(logfile, "\nTCP Пакет:\n");
    print_ip_header(Buffer, Size);
    fprintf(logfile, "\nTCP Заголовок\n");
    fprintf(logfile, "  Порт отправителя     - %d\n", ntohs(tcph->source));
    fprintf(logfile, "  Порт назначения      - %d\n", ntohs(tcph->dest));
    fprintf(logfile, "  Номер пакета         - %u\n", ntohl(tcph->seq));
    fprintf(logfile, "  Номер потверждения   - %u\n", ntohl(tcph->ack_seq));
    fprintf(logfile, "  Длинна заголовка     - %d BYTES\n",(unsigned int) tcph->doff * 4);
    fprintf(logfile, "  Важность             - %d\n", (unsigned int) tcph->urg);
    fprintf(logfile, "  Потверждающий флаг   - %d\n", (unsigned int) tcph->ack);
    fprintf(logfile, "  Push флаг            - %d\n", (unsigned int) tcph->psh);
    fprintf(logfile, "  Reset флаг           - %d\n", (unsigned int) tcph->rst);
    fprintf(logfile, "  Флаг синхронизации   - %d\n", (unsigned int) tcph->syn);
    fprintf(logfile, "  Флаг конца пакета    - %d\n", (unsigned int) tcph->fin);
    fprintf(logfile, "  Размер окна          - %d\n", ntohs(tcph->window));
    fprintf(logfile, "  Чек-сумма            - %d\n", ntohs(tcph->check));
    fprintf(logfile, "  Указатель важности   - %d\n", tcph->urg_ptr);
    fprintf(logfile, "\n");

    fprintf(logfile, "  RAW Заголовок пакета\n");
    PrintData(Buffer, iphdrlen);

    fprintf(logfile, "  RAW Заголовок TCP\n");
    PrintData(Buffer + iphdrlen, tcph->doff * 4);

    fprintf(logfile, "  RAW Данные\n");
    PrintData(Buffer + header_size, Size - header_size);

    fprintf(logfile, "-----------------------------------------------------------");
}
void print_udp_packet(unsigned char *Buffer, int Size) {
    unsigned short iphdrlen;
    struct iphdr *iph = (struct iphdr *) (Buffer + sizeof(struct ethhdr));
    iphdrlen = iph->ihl * 4;

    struct udphdr *udph = (struct udphdr *) (Buffer + iphdrlen + sizeof(struct ethhdr));
    int header_size = sizeof(struct ethhdr) + iphdrlen + sizeof udph;

    fprintf(logfile, "\n-----------------------------------------------------------");

    fprintf(logfile, "\nUDP Пакет:\n");
    print_ip_header(Buffer, Size);
    fprintf(logfile, "\nUDP Заголовок\n");
    fprintf(logfile, "  Порт отправителя    - %d\n", ntohs(udph->source));
    fprintf(logfile, "  Порт назначения     - %d\n", ntohs(udph->dest));
    fprintf(logfile, "  Длинна пакета       - %d\n", ntohs(udph->len));
    fprintf(logfile, "  Чек-сумма           - %d\n", ntohs(udph->check));
    fprintf(logfile, "\n");

    fprintf(logfile, "  RAW Заголовок пакета:\n");
    PrintData(Buffer, iphdrlen);

    fprintf(logfile, "  RAW Заголовок UDP\n");
    PrintData(Buffer + iphdrlen, sizeof udph);

    fprintf(logfile, "  RAW Данные\n");
    PrintData(Buffer + header_size, Size - header_size); //Двигаем указатель на след. данные и сокращаем строку

    fprintf(logfile, "-----------------------------------------------------------");
}
void PrintData(unsigned char *data, int Size) {
    int i, j;
    for (i = 0; i < Size; i++) { //Проходится по каждому байту в буфере данных
        // Вывод символов ASCII в конце каждой строки
        if (i != 0 && i % 16 == 0){   //конец линии
            fprintf(logfile, "         ");
            for (j = i - 16; j < i; j++) {
                if (data[j] >= 32 && data[j] <= 128)
                    fprintf(logfile, "%c", (unsigned char) data[j]); //проверка на символ или цифру
                else fprintf(logfile, "."); //в другом случае печатаем точку
            }
            fprintf(logfile, "\n");
        }

        if (i % 16 == 0) fprintf(logfile, "   ");
        fprintf(logfile, " %02X", (unsigned int) data[i]); //Выводит шестнадцатеричное значение каждого байта, разделенное пробелом

        if (i == Size - 1) {  //печатаем последний пакет
            // Вывод оставшихся символов ASCII в последней строке
            for (j = 0; j < 15 - i % 16; j++) fprintf(logfile, "   "); //ЕЩЕ ПРОБЕЛОВ!!!!
            fprintf(logfile, "         ");

            for (j = i - i % 16; j <= i; j++){
                if (data[j] >= 32 && data[j] <= 128){
                    fprintf(logfile, "%c", (unsigned char) data[j]);
                } else fprintf(logfile, ".");
            }
            fprintf(logfile, "\n");
        }
    }
}
void DaemonMode(){
    int saddr_size,data_size;
    struct sockaddr saddr;
    unsigned char *buffer = (unsigned char *) malloc(65536); // буфер для полученных данных

    if (logfile == NULL) {
        perror("Не удалось создать/открыть файл ＞︿＜");
        exit(0);
    }

    int sock_raw = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock_raw < 0) {
        printf("Запустите программу с sudo! \n");
        perror("Ошибка открытия сокета :-(");
        exit(0);
    }

    printf("Запуск...\n");
    while (1) {
        saddr_size = sizeof saddr;
        data_size = recvfrom(sock_raw, buffer, 65536, 0, &saddr, (socklen_t * ) & saddr_size); //получаем сообщение из сокета
        if (data_size < 0) {
            printf("Не получилось получить данные из сокета\n");
            exit(0);
        }
        ProcessPacket(buffer, data_size);
    }
}

int main(int argc, char **argv) {
    //pid_t parpid;
//    if ((parpid = fork()) < 0) {
//        //printf("\nНеудалось создать дочерний процесс");
//        exit(1);
//    } else if (parpid != 0) exit(0);

    //fprintf(stdout, "Для выключения демона напишите sudo kill %d\n", (int) getpid());
    //setsid(); //перевод нашего дочернего процесса в новую сесию
    logfile = fopen("log.txt", "w");
    DaemonMode();

}
