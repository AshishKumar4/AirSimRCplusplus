#include "DirectControls/DirectControls.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <thread> // std::thread
#include <algorithm>

using namespace std;

/* A Simple program to merely test the APIs */

int main()
{
    DirectController controller("0.0.0.0", 8400);
    int a = 0;
    /*int val = 100;
    for(int i = 0; ; i++)
    {
        cout<<i<<endl;
        controller.setThrottle(val);
        controller.setYaw(val);
        controller.setRoll(val);
        controller.setPitch(val);
        controller.setAux1(val);
        controller.setAux2(val);
        sleep(0.04);
    }
    */
    while (1)
    {
        printf("\nEnter An Option...\n1. Throttle\n2. Yaw\n3. Pitch\n4. Roll\n:>");
        cin >> a;
        printf("\nEnter value : ");
        int val = 0;
        cin >> val;
        switch (a)
        {
        case 1:
            controller.setThrottle(val);
            break;
        case 2:
            controller.setYaw(val);
            break;
        case 3:
            controller.setPitch(val);
            break;
        case 4:
            controller.setRoll(val);
            break;
        case 5:
            controller.setAux1(val);
            break;
        case 6:
            controller.setAux2(val);
            break;
        case 0:
            exit(0);
        default:
            cout << "Incorrect Option choosen!\n";
        }
    }
    return 0;
}