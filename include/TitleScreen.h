#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <allegro_font.h>
#include <allegro_ttf.h>

#include "ScreenManager.h"
#include "GameScreen.h"

class TitleScreen : public GameScreen
{
    public:
        TitleScreen();
        virtual ~TitleScreen();

        void LoadContent();
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev);
        void Draw(ALLEGRO_DISPLAY *display);

    protected:
    private:
        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *logo;
};

#endif // TITLESCREEN_H
