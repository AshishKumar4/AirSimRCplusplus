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

#include "DirectControls.h"

using namespace std;

const char HANDSHAKE_IN_MSG[] = "Hello Gardien!";
const char HANDSHAKE_OUT_MSG[] = "Hello Overloard!";
int opt = 1;
/*
#define PORT_BASE 8300

#define PORT_THROTTLE PORT_BASE + 0
#define PORT_PITCH PORT_BASE + 1
#define PORT_ROLL PORT_BASE + 2
#define PORT_YAW PORT_BASE + 3
#define PORT_AUX1 PORT_BASE + 4
#define PORT_AUX2 PORT_BASE + 5*/

void DirectController::InitSequence()
{
  for (int i = 0; i < 6; i++)
  {
    send(server_fd[i], HANDSHAKE_IN_MSG, strlen(HANDSHAKE_IN_MSG), 0);
    // TODO: Place mechanism to recieve back handshake and if not matching, Panic!
    char *buff = (char *)malloc(1024);
    int valread = read(server_fd[i], buff, 1024);
    if (strncmp(buff, HANDSHAKE_OUT_MSG, strlen(HANDSHAKE_OUT_MSG)))
    {
      std::cout << "Gardien Could not establish Connection / Handshake Failure...\n";
      throw "Handshake Failed!";
    }
    printf("Handshake Successfull, Connection Established!\n");
  }
  disarm();
  balance();
  disarm();
  cout << "Initialization Sequence Completed...\n";
}

DirectController::DirectController(char *ip, int portBase)
{
  ConnectChannel(ip, portBase + 0, 0); //PORT_THROTTLE
  ConnectChannel(ip, portBase + 1, 1); //PORT_PITCH
  ConnectChannel(ip, portBase + 2, 2); //PORT_ROLL
  ConnectChannel(ip, portBase + 3, 3); //PORT_YAW
  ConnectChannel(ip, portBase + 4, 4); //PORT_AUX1
  ConnectChannel(ip, portBase + 5, 5); //PORT_AUX2

  InitSequence();
}

DirectController::~DirectController()
{
}

int DirectController::ConnectChannel(char *ip, int port, int channel) // This would create a port for a particular channel
{
  int sfd;
  struct sockaddr_in *address = new struct sockaddr_in;
  // Creating socket file descriptor
  if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  address->sin_family = AF_INET;
  address->sin_port = htons(port);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, ip, &(address->sin_addr)) <= 0)
  {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  if (connect(sfd, (struct sockaddr *)address, sizeof(struct sockaddr_in)) < 0)
  {
    printf("\nConnection Failed \n");
    return -1;
  }
  try
  {
    if (server_fd.size() <= channel)
    {
      server_fd.push_back(sfd);
      addresses.push_back(address);
    }
    else
    {
      // TODO: Free up the existing sockets
      server_fd[channel] = sfd;
      addresses[channel] = address;
    }
  }
  catch (...)
  {
    perror("Error while Saving the Socket Memory Structures");
    exit(EXIT_FAILURE);
  }
  cout << "Socket for port " << port << " Connected Successfully!" << endl;
  return 0;
}

void DirectController::arm()
{
  cmd(0, 255, 127, 127);
  sleep(1);
  cmd(0, 127, 127, 127);
  cout << "ARMed Successfully...\n";
}

void DirectController::disarm()
{
  cmd(0, 0, 127, 127);
  sleep(1);
  cmd(0, 0, 127, 127);
  cout << "Disarmed Successfully...\n";
}

void DirectController::balance()
{
  cmd(-1, -1, 255, 255);
  sleep(0.01);
  cmd(-1, -1, 127, 127);
}

void DirectController::altitudeHold()
{
  //cmd(-1, -1, 127, 127);
}

/*      APIs for channel Controls       */
void DirectController::cmd(int throttle, int yaw, int roll, int pitch, int aux1, int aux2)
{
  setThrottle(throttle);
  setYaw(yaw);
  setRoll(roll);
  setPitch(pitch);
  setAux1(aux1);
  setAux2(aux2);
}

void DirectController::sendCommand(int val, int channel)
{
  try
  {
    if (val == -1)
    {
      val = channelBuffs[channel];
    }
    else
    {
      channelBuffs[channel] = val;
    }
    stringstream ss;
    ss << ".[:" << val << ":]";
    string msg = ss.str();
    send(server_fd[channel], msg.c_str(), msg.size(), 0);
  }
  catch (exception &e)
  {
    printf("\n{ERROR: %s", e.what());
  }
}

void DirectController::setThrottle(int val)
{
  sendCommand(val, 0);
}

void DirectController::setPitch(int val)
{
  sendCommand(val, 1);
}

void DirectController::setYaw(int val)
{
  sendCommand(val, 3);
}

void DirectController::setRoll(int val)
{
  sendCommand(val, 2);
}

void DirectController::setAux1(int val)
{
  sendCommand(val, 4);
}

void DirectController::setAux2(int val)
{
  sendCommand(val, 5);
}