#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <allegro_font.h>
#include <allegro_ttf.h>

//#include "GameScreen.h"
#include "ScreenManager.h"
#include "FadeAnimation.h"

class SplashScreen : public GameScreen
{
    public:
        SplashScreen();
        virtual ~SplashScreen();

        void LoadContent();
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev);
        void Draw(ALLEGRO_DISPLAY *display);

    protected:
    private:
        ALLEGRO_FONT *font;

        std::vector<FadeAnimation*> fade;//Delete this???
        FadeAnimation fanimation;

};

#endif // SPLASHSCREEN_H
