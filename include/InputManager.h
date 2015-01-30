#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include<allegro.h>
#include<keyboard.h>
#include<vector>

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();

        bool IsKeyPressed(ALLEGRO_EVENT ev, int key);
        bool IsKeyPressed(ALLEGRO_EVENT ev, std::vector<int> keys);
        bool IsKeyReleased(ALLEGRO_EVENT ev, int keys);
        bool IsKeyReleased(ALLEGRO_EVENT ev, std::vector<int> keys);

        bool IsKeyDown(int key);

        void Update();

    protected:


    private:
        ALLEGRO_KEYBOARD_STATE keystate;

};

#endif // INPUTMANAGER_H
