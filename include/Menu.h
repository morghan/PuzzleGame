#include "../include/Grafico.h"
#include "../include/Sonido.h"
#include "../include/irrKlang/irrKlang.h"
#include "../TinyXml/tinyxml.h"
using namespace irrklang;

class Elemento
{
public:
    int x;
    int y;
    int height;
    int width;
    bool visible;


    Elemento(){}

    Elemento(int x, int y, int width, int height,bool visible)
    {
        this->x=x;
        this->y=y;
        this->height=height;
        this->width=width;
        this->visible=visible;
    }

    virtual void dibujar(Grafico*grafico)=0;
    virtual void dibujar(int alineacion_x,int alineacion_y,Grafico*grafico)=0;
    virtual int getTipo()=0;
};

class MenuImagen:Elemento
{
public:
    irr::video::ITexture* imagen;
    irr::video::ITexture* imagen_seleccionado;
    MenuImagen(int x, int y, int width, int height,bool visible,irr::video::ITexture* imagen)
    {
        this->x=x;
        this->y=y;
        this->height=height;
        this->width=width;
        this->visible=visible;
        this->imagen=imagen;
    }
    virtual int getTipo()
    {
        return 2;
    }
    virtual void dibujar(Grafico*grafico)
    {
        grafico->draw2DImage
        (   imagen,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x,y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (0,0),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
    virtual void dibujar(int alineacion_x,int alineacion_y,Grafico*grafico)
    {
        grafico->draw2DImage
        (   imagen,
            irr::core::dimension2d<irr::f32> (width,height),
            irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
            irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
            irr::core::position2d<irr::f32>(0,0),
            irr::f32(0), irr::core::vector2df (0,0),
            true,
            irr::video::SColor(255,255,255,255),
            false,
            false);
    }
};

class MenuTexto:Elemento
{
public:
    stringw texto;
    video::SColor color;
    MenuTexto(int x, int y, int width, int height,bool visible,stringw texto,video::SColor color)
    {
        this->x=x;
        this->y=y;
        this->height=height;
        this->width=width;
        this->visible=visible;
        this->texto=texto;
        this->color=color;
    }
    virtual int getTipo()
    {
        return 3;
    }
    virtual void dibujar(Grafico*grafico)
    {
        grafico->drawText(texto,core::rect<s32>(x,y,x+width,y+height),color);
    }
    virtual void dibujar(int alineacion_x,int alineacion_y,Grafico*grafico)
    {
        grafico->drawText(texto,core::rect<s32>(x+alineacion_x,y+alineacion_y,x+width,y+height),color);
    }
};

class MenuBoton:Elemento
{
public:
    bool seleccionado;
    int accion;

    irr::video::ITexture* imagen;
    stringw texto;
    video::SColor color;
    int alineacion_texto_x,alineacion_texto_y;

    irr::video::ITexture* imagen_sel;
    stringw texto_sel;
    video::SColor color_sel;
    int alineacion_texto_x_sel,alineacion_texto_y_sel;
    MenuBoton(int x, int y, int width, int height,bool visible,
              irr::video::ITexture* imagen,int alineacion_texto_x,int alineacion_texto_y, stringw texto,video::SColor color,
              irr::video::ITexture* imagen_sel,int alineacion_texto_x_sel,int alineacion_texto_y_sel, stringw texto_sel,video::SColor color_sel,
              int accion
              )
    {
        this->x=x;
        this->y=y;
        this->height=height;
        this->width=width;
        this->visible=visible;
        this->imagen=imagen;
        this->texto=texto;
        this->color=color;
        this->alineacion_texto_x=alineacion_texto_x;
        this->alineacion_texto_y=alineacion_texto_y;
        this->imagen_sel=imagen_sel;
        this->texto_sel=texto_sel;
        this->color_sel=color_sel;
        this->alineacion_texto_x_sel=alineacion_texto_x_sel;
        this->alineacion_texto_y_sel=alineacion_texto_y_sel;
        this->seleccionado=false;
        this->accion=accion;
    }
    int getAccion()
    {
        return accion;
    }
    virtual int getTipo()
    {
        return 4;
    }
    virtual void dibujar(Grafico*grafico)
    {
        if(!seleccionado)
        {
            grafico->draw2DImage
            (   imagen,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x,y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->drawText(texto,core::rect<s32>(x+alineacion_texto_x,y+alineacion_texto_y,x+width,y+height),color);
        }else
        {
            grafico->draw2DImage
            (   imagen_sel,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,imagen_sel->getOriginalSize().Width,imagen_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x,y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->drawText(texto_sel,core::rect<s32>(x+alineacion_texto_x_sel,y+alineacion_texto_y_sel,x+width,y+height),color_sel);
        }
    }
    virtual void dibujar(int alineacion_x,int alineacion_y,Grafico*grafico)
    {
        if(!seleccionado)
        {
            grafico->draw2DImage
            (   imagen,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,imagen->getOriginalSize().Width,imagen->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->drawText(texto,core::rect<s32>(x+alineacion_texto_x+alineacion_x,y+alineacion_texto_y+alineacion_y,x+width,y+height),color);
        }else
        {
            grafico->draw2DImage
            (   imagen_sel,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,imagen_sel->getOriginalSize().Width,imagen_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->drawText(texto_sel,core::rect<s32>(x+alineacion_texto_x_sel+alineacion_x,y+alineacion_texto_y_sel+alineacion_y,x+width,y+height),color_sel);
        }
    }
};

class MenuLista:Elemento
{
public:
    irr::video::ITexture*flecha_izquierda;
    irr::video::ITexture*flecha_derecha;
    vector<Elemento*>elementos;
    int flecha_izq_x_sel,flecha_izq_y;
    int flecha_der_x_sel,flecha_der_y;

    irr::video::ITexture*flecha_izquierda_sel;
    irr::video::ITexture*flecha_derecha_sel;
    int flecha_izq_x,flecha_izq_y_sel;
    int flecha_der_x,flecha_der_y_sel;

    int actual;
    bool seleccionado;
    MenuLista(int x, int y, int width, int height,bool visible,
              int flecha_izq_x,int flecha_izq_y,irr::video::ITexture*flecha_izquierda,int flecha_der_x,int flecha_der_y,irr::video::ITexture*flecha_derecha,
              int flecha_izq_x_sel,int flecha_izq_y_sel,irr::video::ITexture*flecha_izquierda_sel,int flecha_der_x_sel,int flecha_der_y_sel,irr::video::ITexture*flecha_derecha_sel,
              vector<Elemento*>elementos
              )
    {
        this->x=x;
        this->y=y;
        this->height=height;
        this->width=width;
        this->visible=visible;

        this->flecha_izq_x=flecha_izq_x;
        this->flecha_izq_y=flecha_izq_y;
        this->flecha_izquierda=flecha_izquierda;
        this->flecha_der_x=flecha_der_x;
        this->flecha_der_y=flecha_der_y;
        this->flecha_derecha=flecha_derecha;

        this->flecha_izq_x_sel=flecha_izq_x_sel;
        this->flecha_izq_y_sel=flecha_izq_y_sel;
        this->flecha_izquierda_sel=flecha_izquierda_sel;
        this->flecha_der_x_sel=flecha_der_x_sel;
        this->flecha_der_y_sel=flecha_der_y_sel;
        this->flecha_derecha_sel=flecha_derecha_sel;

        this->elementos=elementos;
        actual=0;
        seleccionado=false;
    }
    virtual int getTipo()
    {
        return 5;
    }
    void avanzar()
    {
        if(actual<(int)elementos.size()-1)
            actual++;
    }
    void retroceder()
    {
        if(actual>0)
            actual--;
    }
    virtual void dibujar(Grafico*grafico)
    {
        if(!seleccionado)
        {
            if(actual>=0 && actual<(int)elementos.size())
                elementos[actual]->dibujar(x,y,grafico);
            grafico->draw2DImage
            (   flecha_izquierda,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,flecha_izquierda->getOriginalSize().Width,flecha_izquierda->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+flecha_izq_x,y+flecha_izq_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->draw2DImage
            (   flecha_derecha,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,flecha_derecha->getOriginalSize().Width,flecha_derecha->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+flecha_der_x,y+flecha_der_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }else
        {
            if(actual>=0 && actual<(int)elementos.size())
                elementos[actual]->dibujar(x,y,grafico);
            grafico->draw2DImage
            (   flecha_izquierda_sel,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,flecha_izquierda_sel->getOriginalSize().Width,flecha_izquierda_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+flecha_izq_x_sel,y+flecha_izq_y_sel),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->draw2DImage
            (   flecha_derecha_sel,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,flecha_derecha_sel->getOriginalSize().Width,flecha_derecha_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+flecha_der_x_sel,y+flecha_der_y_sel),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }
    }
    virtual void dibujar(int alineacion_x,int alineacion_y,Grafico*grafico)
    {
        if(!seleccionado)
        {
            if(actual>=0 && actual<(int)elementos.size())
                elementos[actual]->dibujar(x+alineacion_x,y+alineacion_y,grafico);
            grafico->draw2DImage
            (   flecha_izquierda,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,flecha_izquierda->getOriginalSize().Width,flecha_izquierda->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+flecha_izq_x+alineacion_x,y+flecha_izq_y+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->draw2DImage
            (   flecha_derecha,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,flecha_derecha->getOriginalSize().Width,flecha_derecha->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+flecha_der_x+alineacion_x,y+flecha_der_y+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }else
        {
            if(actual>=0 && actual<(int)elementos.size())
                elementos[actual]->dibujar(x+alineacion_x,y+alineacion_y,grafico);
            grafico->draw2DImage
            (   flecha_izquierda_sel,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,flecha_izquierda_sel->getOriginalSize().Width,flecha_izquierda_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+flecha_izq_x_sel+alineacion_x,y+flecha_izq_y_sel+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->draw2DImage
            (   flecha_derecha_sel,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,flecha_derecha_sel->getOriginalSize().Width,flecha_derecha_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+flecha_der_x_sel+alineacion_x,y+flecha_der_y_sel+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }
    }
};

class MenuBarra:Elemento
{
public:
    irr::video::ITexture*fondo;
    irr::video::ITexture*barra;
    int barra_x,barra_y;

    irr::video::ITexture*fondo_sel;
    irr::video::ITexture*barra_sel;
    int barra_x_sel,barra_y_sel;

    int maximo,actual;

    bool seleccionado;
    MenuBarra(int x, int y, int width, int height,bool visible,
              irr::video::ITexture*fondo,int barra_x,int barra_y,irr::video::ITexture*barra,
              irr::video::ITexture*fondo_sel,int barra_x_sel,int barra_y_sel,irr::video::ITexture*barra_sel,
              int maximo,int actual)
    {
        this->x=x;
        this->y=y;
        this->height=height;
        this->width=width;
        this->visible=visible;

        this->fondo=fondo;
        this->barra=barra;
        this->barra_x=barra_x;
        this->barra_y=barra_y;

        this->fondo_sel=fondo_sel;
        this->barra_sel=barra_sel;
        this->barra_x_sel=barra_x_sel;
        this->barra_y_sel=barra_y_sel;

        this->maximo=maximo;
        this->actual=actual;
        this->seleccionado=false;
    }
    virtual int getTipo()
    {
        return 6;
    }
    void avanzar()
    {
        if(actual<maximo)
            actual++;
    }
    void retroceder()
    {
        if(actual>0)
            actual--;
    }
    virtual void dibujar(Grafico*grafico)
    {
        if(!seleccionado)
        {
            grafico->draw2DImage
            (   fondo,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,fondo->getOriginalSize().Width,fondo->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x,y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->draw2DImage
            (   barra,
                irr::core::dimension2d<irr::f32> (width*(actual/maximo),height),
                irr::core::rect<irr::f32>(0,0,barra->getOriginalSize().Width,barra->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+barra_x,y+barra_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }else
        {
            grafico->draw2DImage
            (   fondo_sel,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,fondo_sel->getOriginalSize().Width,fondo_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x,y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->draw2DImage
            (   barra_sel,
                irr::core::dimension2d<irr::f32> (width*(actual/maximo),height),
                irr::core::rect<irr::f32>(0,0,barra_sel->getOriginalSize().Width,barra_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+barra_x_sel,y+barra_y_sel),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }
    }
    virtual void dibujar(int alineacion_x,int alineacion_y,Grafico*grafico)
    {
        if(!seleccionado)
        {
            grafico->draw2DImage
            (   fondo,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,fondo->getOriginalSize().Width,fondo->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->draw2DImage
            (   barra,
                irr::core::dimension2d<irr::f32> (width*((float)actual/(float)maximo),height),
                irr::core::rect<irr::f32>(0,0,barra->getOriginalSize().Width*((float)actual/(float)maximo),barra->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+barra_x+alineacion_x,y+barra_y+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }else
        {
            grafico->draw2DImage
            (   fondo_sel,
                irr::core::dimension2d<irr::f32> (width,height),
                irr::core::rect<irr::f32>(0,0,fondo_sel->getOriginalSize().Width,fondo_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+alineacion_x,y+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
            grafico->draw2DImage
            (   barra_sel,
                irr::core::dimension2d<irr::f32> (width*((float)actual/(float)maximo),height),
                irr::core::rect<irr::f32>(0,0,barra_sel->getOriginalSize().Width*((float)actual/(float)maximo),barra_sel->getOriginalSize().Height),
                irr::core::position2d<irr::f32>(x+barra_x_sel+alineacion_x,y+barra_y_sel+alineacion_y),
                irr::core::position2d<irr::f32>(0,0),
                irr::f32(0), irr::core::vector2df (1,1),
                true,
                irr::video::SColor(255,255,255,255),
                false,
                false);
        }
    }
};

class MenuContenedor:Elemento
{
public:
    vector<Elemento*> elementos;
    int seleccionado;
    MenuContenedor(int x, int y, int width, int height,bool visible,vector<Elemento*> elementos)
    {
        this->x=x;
        this->y=y;
        this->height=height;
        this->width=width;
        this->visible=visible;
        this->elementos=elementos;
        this->seleccionado=0;
        for(int i=0;i<(int)elementos.size();i++)
            if(elementos[i]->getTipo()==4 || elementos[i]->getTipo()==5 || elementos[i]->getTipo()==6)
            {
                if(elementos[i]->getTipo()==4)
                    ((MenuBoton*)elementos[i])->seleccionado=true;
                if(elementos[i]->getTipo()==5)
                    ((MenuLista*)elementos[i])->seleccionado=true;
                if(elementos[i]->getTipo()==6)
                    ((MenuBarra*)elementos[i])->seleccionado=true;
                seleccionado=i;
                break;
            }

    }
    virtual int getTipo()
    {
        return 1;
    }
    virtual void dibujar(Grafico*grafico)
    {
        for(int i=0;i<(int)elementos.size();i++)
            elementos[i]->dibujar(x,y,grafico);
    }
    virtual void dibujar(int alineacion_x,int alineacion_y,Grafico*grafico)
    {
        for(int i=0;i<(int)elementos.size();i++)
            elementos[i]->dibujar(x+alineacion_x,y+alineacion_y,grafico);
    }
    void avanzar()
    {
        for(int i=seleccionado+1;i<(int)elementos.size();i++)
            if(elementos[i]->getTipo()==4 || elementos[i]->getTipo()==5 || elementos[i]->getTipo()==6)
            {
                if(elementos[seleccionado]->getTipo()==4)
                    ((MenuBoton*)elementos[seleccionado])->seleccionado=false;
                if(elementos[seleccionado]->getTipo()==5)
                    ((MenuLista*)elementos[seleccionado])->seleccionado=false;
                if(elementos[seleccionado]->getTipo()==6)
                    ((MenuBarra*)elementos[seleccionado])->seleccionado=false;

                if(elementos[i]->getTipo()==4)
                    ((MenuBoton*)elementos[i])->seleccionado=true;
                if(elementos[i]->getTipo()==5)
                    ((MenuLista*)elementos[i])->seleccionado=true;
                if(elementos[i]->getTipo()==6)
                    ((MenuBarra*)elementos[i])->seleccionado=true;
                seleccionado=i;
                break;
            }
    }
    void retroceder()
    {
        for(int i=seleccionado-1;i>=0;i--)
            if(elementos[i]->getTipo()==4 || elementos[i]->getTipo()==5 || elementos[i]->getTipo()==6)
            {
                if(elementos[seleccionado]->getTipo()==4)
                    ((MenuBoton*)elementos[seleccionado])->seleccionado=false;
                if(elementos[seleccionado]->getTipo()==5)
                    ((MenuLista*)elementos[seleccionado])->seleccionado=false;
                if(elementos[seleccionado]->getTipo()==6)
                    ((MenuBarra*)elementos[seleccionado])->seleccionado=false;

                if(elementos[i]->getTipo()==4)
                    ((MenuBoton*)elementos[i])->seleccionado=true;
                if(elementos[i]->getTipo()==5)
                    ((MenuLista*)elementos[i])->seleccionado=true;
                if(elementos[i]->getTipo()==6)
                    ((MenuBarra*)elementos[i])->seleccionado=true;
                seleccionado=i;
                break;
            }
    }
    Elemento* getSeleccionado()
    {
        return elementos[seleccionado];
    }
};

class Menu
{
public:
    //Engines
    Sonido* sonido;
    Grafico* grafico;
    Receiver* receiver;

    vector<Elemento*> elementos;

    MenuContenedor*contenedor_actual;

    Menu(){}
    Menu(Grafico* grafico,Receiver* receiver);
    void loopMenu();
    void dibujarMenu();
    void cargarDesdeXml(char*archivo);
    TiXmlDocument abrirXml(char* archivo);
    char* getPersonajeA()
    {
        MenuContenedor *mc=(MenuContenedor*)elementos[4];
        MenuLista *ml=(MenuLista*)mc->elementos[1];
        MenuTexto *mt=(MenuTexto*)ml->elementos[ml->actual];
        stringw s2=mt->texto;
        char *str = new char[255];
        sprintf(str,"%ls",s2.c_str());
        return str;
    }
    char* getPersonajeB()
    {
        MenuContenedor *mc=(MenuContenedor*)elementos[4];
        MenuLista *ml=(MenuLista*)mc->elementos[2];
        MenuTexto *mt=(MenuTexto*)ml->elementos[ml->actual];
        stringw s2=mt->texto;
        char *str = new char[255];
        sprintf(str,"%ls",s2.c_str());
        return str;
    }
    char* getStage()
    {
        MenuContenedor *mc=(MenuContenedor*)elementos[4];
        MenuLista *ml=(MenuLista*)mc->elementos[3];
        MenuTexto *mt=(MenuTexto*)ml->elementos[ml->actual];
        stringw s2=mt->texto;
        char *str = new char[255];
        sprintf(str,"%ls",s2.c_str());
        return str;
    }
};
