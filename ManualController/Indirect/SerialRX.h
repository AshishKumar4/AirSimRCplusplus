#pragma once

#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <stdio.h>
#include <stdlib.h>

class SerialRX
{
    FILE* serialFile;
    char* buffer;
  private:
  public:
    SerialRX(char *portName);
    ~SerialRX();

    string getBuff(int size);
};

#endif // SERIALPORT_H