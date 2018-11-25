#ifndef SPI_DRIVERS
#define SPI_DRIVERS

#define SPI_SPEED 1000000

/*
    SPI Drivers, to send and recieve data packets over SPI
*/

int SPI_init(char* file);
int SPI_ReadWrite(int fd, uintptr_t writebuff, uintptr_t readbuff, size_t len);
int SPI_send(int fd, uintptr_t buffer, size_t len);
int SPI_read(int fd, uintptr_t buffer, size_t len);

#endif