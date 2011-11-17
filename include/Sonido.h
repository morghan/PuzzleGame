#include "../include/irrKlang/irrKlang.h"
//using namespace System;
//using namespace System.IO;
using namespace irrklang;
#include <irrlicht/irrlicht.h>
using namespace irr;
#include <string>
#include <vector>

class Reproduccion
{
public:
    Reproduccion(ISoundSource* source)
    {
        this->source=source;
    }
    ISound* sonido;
    ISoundSource* source;
};

class Sonido
{
    ISoundEngine *engine;
    irr::core::map<std::string,Reproduccion*> sonidos;
public:
    Sonido();
    void drop();
    void agregarSonido(std::string variable,const ik_c8* valor);
    void reproducirSonido(std::string variable);
    void pararSonido(std::string variable);
    void setVolumen(std::string variable,float volumen);
};
