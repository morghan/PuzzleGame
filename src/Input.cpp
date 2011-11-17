#include "../include/Input.h"

Receiver::Receiver()
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

bool Receiver::OnEvent(const SEvent& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    //Joystick
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 0)
    {
            JoystickState0 = event.JoystickEvent;
    }
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 1)
    {
            JoystickState1 = event.JoystickEvent;
    }
    return false;
}

const SEvent::SJoystickEvent & Receiver::GetJoystickState(void) const
{
    if(joystick==0)
        return JoystickState0;
    if(joystick==1)
        return JoystickState1;
    return JoystickState0;;
}

bool Receiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

bool Receiver::IsJoyDown(int joyCode,int joystick)
{
    this->joystick=joystick;
    const SEvent::SJoystickEvent & joystickData = GetJoystickState();
    moveHorizontal=(f32)GetJoystickState().Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
    moveVertical=(f32)GetJoystickState().Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
    if(moveVertical<0 && joyCode==-2)
        return true;
    if(moveHorizontal<0 && joyCode==-4)
        return true;
    if(moveHorizontal>0 && joyCode==-6)
        return true;
    if(moveVertical>0 && joyCode==-8)
        return true;
    if(joystickData.IsButtonPressed(joyCode))
        return true;
    return false;
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

Input::Input(vector<Boton> botones,Receiver* receiver)
{
    this->receiver=receiver;
    tecla_arriba=true;
    for(int i=0;i<(int)botones.size();i++)
        if(botones[i].getMapeo()=="2" || botones[i].getMapeo()=="4" || botones[i].getMapeo()=="6" || botones[i].getMapeo()=="8")
            this->cruz.push_back(botones[i]);
        else
            this->botones.push_back(botones[i]);
}

stringw Input::getInput()
{
    stringw resultado="";
    for(int i=0;i<(int)cruz.size();i++)
        if(cruz[i].estaPresionado(receiver))
            resultado+=cruz[i].getMapeo();
    if(resultado=="24" || resultado=="42")
        resultado="1";
    if(resultado=="26" || resultado=="62")
        resultado="3";
    if(resultado=="84" || resultado=="48")
        resultado="7";
    if(resultado=="68" || resultado=="86")
        resultado="9";
    if(tecla_arriba)
    {
        tecla_arriba=false;
        for(int i=0;i<(int)botones.size();i++)
            if(botones[i].estaPresionado(receiver))
                resultado+=botones[i].getMapeo();
    }
    bool flag=false;
    for(int i=0;i<(int)botones.size();i++)
        if(botones[i].estaPresionado(receiver))
            flag=true;
    if(!flag)
        tecla_arriba=true;
    if(resultado=="")
        resultado="5";
    return resultado;
}
