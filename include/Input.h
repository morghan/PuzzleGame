#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdarg.h>
using namespace std;

#include <irrlicht/irrlicht.h>
#include "../TinyXml/tinyxml.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Receiver : public IEventReceiver
{
private:
    f32 moveHorizontal;
    f32 moveVertical;
    SEvent::SJoystickEvent JoystickState0;
    SEvent::SJoystickEvent JoystickState1;
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    virtual bool OnEvent(const SEvent& event);
    const SEvent::SJoystickEvent & GetJoystickState(void) const;
    int joystick;

public:
    Receiver();
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;
    bool IsJoyDown(int joyCode,int joystick);
};

class Boton
{
private:
    irr::EKEY_CODE teclado;
    int joystick;
    stringw mapeo;
    bool usando_joystick;
public:
int num_joystick;
    Boton()
    {

    }
    Boton(irr::EKEY_CODE teclado,stringw mapeo)
    {
        this->teclado=teclado;
        this->mapeo=mapeo;
        usando_joystick=false;
    }
    Boton(int joystick,int num_joystick,stringw mapeo)
    {
        this->num_joystick=num_joystick;
        this->joystick=joystick;
        this->mapeo=mapeo;
        usando_joystick=true;
    }

    bool estaPresionado(Receiver* receiver)
    {
        if(usando_joystick)
        {
            if(receiver->IsJoyDown(joystick,num_joystick))/////
                return true;
        }else
        {
            if (receiver->IsKeyDown(teclado))
                return true;
        }
        return false;
    }

    stringw getMapeo()
    {
        return mapeo;
    }
};

class Input
{
protected:
    bool tecla_arriba;
    vector<Boton> cruz;
    vector<Boton> botones;
public:
Receiver* receiver;
    Input(){}
    Input(vector<Boton> botones,Receiver* receiver);
    stringw getInput();
};
#endif // MYEVENTRECEIVER_H
