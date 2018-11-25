#include "stdio.h"
#include "iostream"
#include "vector"
#include "string"
#include <algorithm>
#include "stdio.h"
#include "string.h"
#include "cstring"

using namespace std;

#include "SerialRX.h"

SerialRX::SerialRX(char* portName)
{
    buffer = new char[8192];
    serialFile = fopen(portName, "r");
    //fread(buffer, 1000, 1, file);
}

string SerialRX::getBuff(int size)
{
    fread(buffer, size, 1, serialFile);
    //strcpy(buffer, "1242 1438 1236 1485 1240 1240\n1242 1438 1236 1485 1240 1240\n1242 1438 1236 1485 1240 1240\n1242 1438 1236 1485 1240 1240\n1242 1438 1236 1485 1240 1240\n1242 1438 1236 1485 1240 1240\n");
    /*int i;
    for(i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++);
    buffer += i + 1;*/
    return string(buffer);
}