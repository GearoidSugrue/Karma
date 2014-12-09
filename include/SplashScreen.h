#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <allegro_font.h>
#include <allegro_ttf.h>

#include "GameScreen.h"

class SplashScreen : public GameScreen
{
    public:
        SplashScreen();
        virtual ~SplashScreen();

        virtual void LoadContent();
        virtual void UnloadContent();
        virtual void Update(ALLEGRO_EVENT ev);
        virtual void Draw(ALLEGRO_DISPLAY *display);

    protected:
    private:

        ALLEGRO_FONT *font;


};

#endif // SPLASHSCREEN_H
