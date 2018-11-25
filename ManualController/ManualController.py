from socket import * 
from time import *

class RemoteControl:
    def __init__(self, ip = '127.0.0.1', base_port = 8400):
        self.s = list()
        for i in range(0, 6):
            self.s.append(socket(AF_INET, SOCK_STREAM))
            self.s[i].connect((ip, base_port + i))
            self.s[i].send(b'Hello Gardien!') # The Handshake Message
            if(self.s[i].recv(1024) != b'Hello Overloard!'):
                raise Exception("Could Not Connect to the Drone Control Server!")        
        self.y = 0
        self.r = self.p = 0
        self.t = 0
        self.a1 = 0
        self.a2 = 0
        self.disarm()
        sleep(0.01)
        self.cmd(0, 0, 0, 0)#(b'T:0 Y:0 R:0 P:0 C:0') # Set everything to 0
        #print(self.s.recv(1024))
        sleep(0.01)
        self.cmd(255, 255, 255, 255)#(b'T:255 Y:255: R:255 P:255 C:0')
        sleep(0.01)
        self.cmd(0, 0, 127, 127)#(b'T:0 Y:0 R:127 P:127 C:0')
        sleep(0.01)
        self.balance()
        self.y = 0
        self.r = self.p = 127
        self.t = 0
        self.a1 = 0
        self.a2 = 0
        return 
    def arm(self):
        self.cmd(0, 255, 127, 127)#(b'T:0 Y:255 R:127 P:127 C:0')
        sleep(1)
        self.cmd(0, 127, 127, 127)#(b'T:0 Y:127 R:127 P:127 C:0')
        self.y = self.r = self.p = 127
        print('ARMed Successfully...')
        return True
    def disarm(self):
        self.cmd(0, 0, 127, 127)#(b'T:0 Y:0 R:127 P:127 C:0')
        self.y = 0
        self.r = self.p = 127
        print('Disarmed Successfully...')
        return True
    def balance(self):
        self.cmd(-1, -1, 255, 255)#(b'R:255 P:255 C:0')
        sleep(0.01)
        self.cmd(-1, -1, 127, 127)#(b'R:127 P:127 C:0')
    def cmd(self, throttle = -1, yaw = -1, roll = -1, pitch = -1, aux1 = -1, aux2 = -1):
        self.setThrottle(throttle)
        self.setYaw(yaw)
        self.setRoll(roll)
        self.setPitch(pitch)
        self.setAux1(aux1)
        self.setAux2(aux2)
    def setThrottle(self, val = -1):
        if val == -1:
            val = self.t
        else:
            self.t = val
        ss = bytes(str(val), "utf-8")
        self.s[0].send(b'.[:'+ss+b':]')
    def setPitch(self, val = -1):
        if val == -1:
            val = self.p
        else:
            self.p = val
        ss = bytes(str(val), "utf-8")
        self.s[1].send(b'.[:'+ss+b':]')
    def setRoll(self, val = -1):
        if val == -1:
            val = self.r
        else:
            self.r = val
        ss = bytes(str(val), "utf-8")
        self.s[2].send(b'.[:'+ss+b':]')
    def setYaw(self, val = -1):
        if val == -1:
            val = self.y
        else:
            self.y = val
        ss = bytes(str(val), "utf-8")
        self.s[3].send(b'.[:'+ss+b':]')
    def setAux1(self, val = -1):
        if val == -1:
            val = self.a1
        else:
            self.a1 = val
        ss = bytes(str(val), "utf-8")
        self.s[4].send(b'.[:'+ss+b':]')
    def setAux2(self, val = -1):
        if val == -1:
            val = self.a2
        else:
            self.a2 = val
        ss = bytes(str(val), "utf-8")
        self.s[5].send(b'.[:'+ss+b':]')


r = RemoteControl(ip = "192.168.43.98")
