#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <allegro_font.h>
#include <allegro_ttf.h>

#include "ScreenManager.h"
#include "GameScreen.h"

class EndScreen : public GameScreen
{
    public:
        EndScreen();
        virtual ~EndScreen();

        virtual void LoadContent();
        virtual void UnloadContent();
        virtual void Update(ALLEGRO_EVENT ev);
        virtual void Draw(ALLEGRO_DISPLAY *display);

    protected:
    private:
        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *logo;

};

#endif // ENDSCREEN_H
