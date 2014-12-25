#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include<allegro.h>
#include <allegro_primitives.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include"InputManager.h"
#include"FadeAnimation.h"

//Acts like an interface
class GameScreen
{
    public:
        GameScreen();
        virtual ~GameScreen();

        virtual void LoadContent();//virtual so GameScreen sub-classescan overwrite these frunctions
        virtual void UnloadContent();
        virtual void Update(ALLEGRO_EVENT ev);
        virtual void Draw(ALLEGRO_DISPLAY *display);

        InputManager GetInput();
        std::pair<float, float> cameraPosition;

    protected:
        InputManager input;

    private:

};

#endif // GAMESCREEN_H
