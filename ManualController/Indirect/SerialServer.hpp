#include <iostream>
#include <fstream>
#include "string"

int main(int argc, char* argv[])
{/*
	//open arduino device file (linux)
        std::wistream arduino;
	arduino.open( "/dev/ttyACM0");

	//write to it
     std::string test;
     arduino >> test;
     std::cout<< test;
	arduino.close();
*/
    FILE *file;
    file = fopen("/dev/ttyACM0", "r");
    char* buff = new char[1000];
    fread(buff, 1000, 1, file);
    std::cout<<buff;
	return 0;
}