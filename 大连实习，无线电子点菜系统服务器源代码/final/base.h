#ifndef _BASE_H
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

#define BAUDRATE B9600
#define MODEMDEVICE  "/dev/ttyS1"
#define DM_BASE_REST_COM 0x04
#define BASE_AUTOSEND_COM 0x16
#define COM_ACCEPTED 0x30
#define BASE_RESET_COMPLETE 0x04
#define COM_NO_OP 0x31
#define RESPONSE_TIMEOUT 0x32
#define NETWORK_TIMEOUT 0x33
#define RESPONSE_ERROR 0x34
#define SERIAL_ERROR 0x35
#define INVALID_LENGTH 0x36
#define INVALID_DLE_SEQUENCE 0x37

#define DLE 0x10
#define STX 0x02

#define ETX 0x03
#define I_O_COM 0x60
#define I_O_RES 0xE0
#define UART_SEND 0x41
#define UART_RES 0x49


#endif
