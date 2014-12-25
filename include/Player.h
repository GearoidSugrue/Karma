#ifndef PLAYER_H
#define PLAYER_H

#include<allegro.h>
#include<iostream>

#include"InputManager.h"
#include"Animation.h"


class Player
{
    public:
        Player();
        virtual ~Player();

        void LoadContent();
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev, InputManager input);
        void Draw(ALLEGRO_DISPLAY *display);

        void SetKarmaLevel(int newLevel);
        int  GetKarmaLevel();
        void SetMoney(int newAmount);
        int  GetMoney();
        std::pair<float, float> GetPosition();

    protected:
    private:
        ALLEGRO_BITMAP *playerImage;
        std::pair<float, float> position;
        std::pair<float, float> vel;
        float moveSpeed;
        float jumpspeed;
        float gravity;
        int cashAmount;
        int karmaLevel;
        bool activateGravity;

        Animation playerAnimation;
};

#endif // PLAYER_H
