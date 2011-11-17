#include "../include/Sonido.h"

Sonido::Sonido()
{
    engine=createIrrKlangDevice();
}
void Sonido::drop()
{
    engine->drop();
}
void Sonido::agregarSonido(std::string variable,const ik_c8* valor)
{
    sonidos[variable]=new Reproduccion(engine->addSoundSourceFromFile(valor));
}
void Sonido::reproducirSonido(std::string variable)
{
    Reproduccion* rep=sonidos[variable];
    rep->sonido=engine->play2D(rep->source,false,false,true,true);
}

void Sonido::pararSonido(std::string variable)
{
    Reproduccion* rep=sonidos[variable];
    rep->sonido->stop();
}

void Sonido::setVolumen(std::string variable,float volumen)
{
    Reproduccion* rep=sonidos[variable];
    rep->sonido->setVolume(volumen);
}
