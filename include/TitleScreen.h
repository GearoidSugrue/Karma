#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <allegro_font.h>
#include <allegro_ttf.h>

#include "ScreenManager.h"
//#include "InputManager.h"

class TitleScreen : public GameScreen
{
    public:
        TitleScreen();
        virtual ~TitleScreen();

 virtual void LoadContent();
        virtual void UnloadContent();
        virtual void Update(ALLEGRO_EVENT ev);
        virtual void Draw(ALLEGRO_DISPLAY *display);

    protected:
    private:

        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *logo;
        //InputManager input;


};

#endif // TITLESCREEN_H
