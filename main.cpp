#include <iostream>
#include "include/Menu.h"
using namespace std;

void probaEstaFuncionAntesJerzon()
{
    //CHECKPOINT!
    //Level 2 Receiver y Grafico
    //Receiver: recibidor de inputs de teclas y joystick desde la ventanita
    Receiver *receiver=new Receiver();
    //Grafico: dibuja en la ventanita
    Grafico *grafico=new Grafico(receiver);

    Menu *menu=new Menu(grafico,receiver);//Inicializacion:
    menu->loopMenu();//Loop de dibujo de menu

    //Practica: Ver como dibuja "grafico" y como recibe inputs "recevier"
    for(;;)//Paja
    {
	    grafico->device->getTimer()->start();//Paja
	    for(u32 t=grafico->device->getTimer()->getTime();//Paja
            t+16>grafico->device->getTimer()->getTime();//Paja
            grafico->device->getTimer()->tick()//Paja
         );//Paja
        if (grafico->isWindowActive())//Paja
        {//Paja
            grafico->beginScene();//Paja

            if(receiver->IsKeyDown(irr::KEY_ESCAPE))//  <--- Aqui uso receiver!!!!!!!
                break;

            grafico->draw2DImage                   //  <--- Aqui uso grafico!!!!!!!
            (   grafico->getTexture("imagen.png"),
                irr::core::dimension2d<irr::f32> (100,200), //tamaño de la imagen
                irr::core::rect<irr::f32>(0,0,100,200), //Rectangulo de recorte de imagen
                irr::core::position2d<irr::f32>(0,0), //Posicion x y en la pantalla
                irr::core::position2d<irr::f32>(0,0), //Centro de rotacion de la imagen
                irr::f32(0), irr::core::vector2df (1,1), //escala x y
                true,// Acepta canal alpha
                irr::video::SColor(255,255,255,255),//Color de.. ehh no se d q :s
                false,//Flip horizontal
                false);//Flip vertical

            grafico->draw2DImage                   //  <--- Aqui uso grafico!!!!!!!
            (   grafico->getTexture("kawaii.png"),
                irr::core::dimension2d<irr::f32> (38,200), //tamaño de la imagen
                irr::core::rect<irr::f32>(0,0,38,200), //Rectangulo de recorte de imagen
                irr::core::position2d<irr::f32>(0,200), //Posicion x y en la pantalla
                irr::core::position2d<irr::f32>(0,0), //Centro de rotacion de la imagen
                irr::f32(0), irr::core::vector2df (1,1), //escala x y
                true,// Acepta canal alpha
                irr::video::SColor(255,255,255,255),//Color de.. ehh no se d q :s
                false,//Flip horizontal
                false);//Flip vertical

            grafico->endScene();//Paja
        }
        grafico->run();//Paja
    }

    //CHECKPOINT!!
    //Level 3: Menu
    //El menu se define desde el xml en "menu/menu.xml"
    //Descomenta las siguientes 2 lineas

    //Menu *menu=new Menu(grafico,receiver);//Inicializacion:
    //menu->loopMenu();//Loop de dibujo de menu

    //Te recomendaria no meterte a rollo de como funciona ahora
    //Solo importan 2 cosas:
    //  1) Con iniciar hace un break al loop del menu para q siga el programa
    //  2) Con salir hace un exit(0) del saliendo programa
}

int main()
{
    //Bienvenido al tutorial ready? fiiiihtkjsdhfak!
    //Level 1: Obedece a la morsa
    //Inicio: Hacele caso al cout
    cout<<"Descomenta la funcion de abajo (\"probaEstaFuncionAntesJerzon\")"<<endl;
    probaEstaFuncionAntesJerzon();

    //Level 4: Ready to roll sir
    //Borra todo esto y hace tus clases :D
    //<Musica de final fantasy>

    return 0;
}
