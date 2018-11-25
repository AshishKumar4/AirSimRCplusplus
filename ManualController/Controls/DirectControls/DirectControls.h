#ifndef DIRECT_CONTROLS_H
#define DIRECT_CONTROLS_H

#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <thread> // std::thread

#include "../AbstractControls/Controls.hpp"

class DirectController : public Controller
{
  vector<int> server_fd;
  vector<int> socket_num;
  vector<struct sockaddr_in *> addresses;
  int channelBuffs[6] = {0, 0, 0, 0, 0, 0};

protected:
  void sendCommand(int val, int channel);
public:
  void InitSequence();
  int ConnectChannel(char *ip, int port, int channel);
  DirectController(char *ip = "0.0.0.0", int portBase = 8400);
  ~DirectController();
  void arm();
  void disarm();
  void balance();
  void altitudeHold();
  /*      APIs for channel Controls       */
  void cmd(int throttle, int yaw, int roll, int pitch, int aux1 = 0, int aux2 = 0);
  void setThrottle(int val);
  void setPitch(int val);
  void setYaw(int val);
  void setRoll(int val);
  void setAux1(int val);
  void setAux2(int val);
};

#endif