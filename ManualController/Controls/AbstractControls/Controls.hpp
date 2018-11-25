#pragma once

#include "iostream" 
#include "vector"

using namespace std;

class Controller    // An Abstract Class to provide APIs for Controls
{
protected:
public:
    Controller()
    {

    }
    ~Controller()
    {

    }

    /*      APIs for channel Controls       */
    virtual void setThrottle(int val)  =   0;
    virtual void setPitch(int val)  =   0;
    virtual void setYaw(int val)  =   0;
    virtual void setRoll(int val)  =   0;
    virtual void setAux1(int val)  =   0;
    virtual void setAux2(int val)  =   0;    
};