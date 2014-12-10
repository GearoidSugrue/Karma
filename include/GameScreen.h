#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include<allegro.h>
#include"InputManager.h"
#include <iostream>

class GameScreen
{
    public:
        GameScreen();
        virtual ~GameScreen();

        virtual void LoadContent();
        virtual void UnloadContent();
        virtual void Update(ALLEGRO_EVENT ev);
        virtual void Draw(ALLEGRO_DISPLAY *display);

        InputManager GetInput();

    protected:
        InputManager input;
        //std::vector< std::vector<std::string> > attributes;
        //std::vector< std::vector<std::string> > contents;

    private:


};

#endif // GAMESCREEN_H
