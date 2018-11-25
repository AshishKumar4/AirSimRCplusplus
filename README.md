# Use any Radio Controller easily with AirSimRC++
## This software stack allows you to integrate any Radio Controller hasle-free, to use with Unreal Engine 4 based AirSim Simulator as well as to provide extended APIs for general use.
### Wanted to use your Radio Controller but its not supported by AirSim? or just wanted to get data from a Radio Controller to a PC for god knows what reason? Well this might just end your search.

## AirSimRC++ allows you to connect your random radio controller to a PC, via an **_intermediate Arduino_** (or stm8/32 or any other microcontroller really), and provide a useful set of APIs and tools to do stuff with the data, for example, connect to the AirSim Simulator of Unreal Engine 4, without **_EXPLICITLY coding for a new RX_**.

### **For the Architecture, check the bottom note**

## **_Usage:_**
>First upload the **_ArduinoInterface_** sketch onto an arduino board (or stm etc.). Tweak the serial speed as the max available on that board.
>**_Connect the board to the Reciever_**, All signal pins on PWM pins of the Arduino. If required, change the pin layout in the sketch as necessary.
>**_Launch Unreal Engine 4_** and a **_project configured with AirSim_**, and hit **_'Play'_**
>Execute the **_AirSimControls.py_** script (rom the **_AirSim Handler_** folder) using Python 3. Terminal -> **_python3 AirSimControls.py_**
>Open a terminal in the **_ManualController_** Directory and type **_make_** to compile and generate binaries.
>**_Switch on the Radio controller_** and make sure it is binded to the reciever.
>**_Execute the ManualController_** Binary. 
>Procedures to calibrate the controller follows. First **_both joysticks to bottom_**, then **_top_**, then **_left_** then **_right_** then **_leave in middle_**. Then **_Wait for 5 seconds_** for the procedure to finish.

###Following the steps, You should now be able to fly the MultiCopter using the controller, intuitively. Report any bugs/problems if found. 

### **_The Architecture is as follows_**
The Radio Reciever is **connected to an Arduino**, with **provided Code uploaded on it**. The Radio Reciever sends data recieved from the transmitter via _PWM_ signals. Arduino then writes the data onto a _Serial_ port as stream to a PC attached. 
The **_ManualController_** Program reads from this Serial port, unpacks the data, calibrates it when needed, and applies some signal processing to sanitize and smoothen it, and converts it into a range of _0-255_. **_ManualController_** program then connects to a local server, created by the **_AirSimControls.py_** and begins sending RX data over via sockets.
The **_AirSimControls.py_** is a Python 3 script that connects to the AirSim module running along Unreal Engine 4, sets up a local server, listens for RX data from **_ManualController_**, and then calls AirSim's internal APIs to forward the commands and thus control the virtual drone as if real.
One might wonder why so much trouble setting up local servers and passing data via sockets. well, This code is a part of a greater project, where I needed to control a Real Drone, via a PC itself. This ManualController was developed to just test all the protocols and APIs involved. And to test the offboard side of things, I created a simple 'Drone Emulating' server, which mimicked the Drone's APIs that I had developed, but instead of commanding a real drone, commanded a virtual one in Unreal Engine itself. I thought this can be useful for someone as a standalone system itself, thus this. 
The overhead of data transfers isn't significant as compared to the main bottleneck, which is the Reciever to Arduino communication, which can't be optimized.
Still, Suggestions, Bug alerts and possible fixes as well as any optimization you well are welcomed, Do open a pull request.

