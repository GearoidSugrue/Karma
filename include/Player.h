#ifndef PLAYER_H
#define PLAYER_H

#include<allegro.h>
#include<iostream>

#include"InputManager.h"
#include"SpriteSheetAnimation.h"

class Player
{
    public:
        Player();
        virtual ~Player();

        void LoadContent();
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev);//, InputManager input);
        void Draw(ALLEGRO_DISPLAY *display);
        void SetKarmaLevel(int newLevel);
        int  GetKarmaLevel();

    protected:
    private:
        ALLEGRO_BITMAP *playerImage;
        float position[2];
        float moveSpeed;
        int karmaLevel;

        Animation playerAnimation;
        SpriteSheetAnimation spriteAnimation;
};

#endif // PLAYER_H
