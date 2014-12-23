#ifndef PLAYER_H
#define PLAYER_H

#include<allegro.h>//Entity class has all of this already
#include<iostream>

#include"InputManager.h"
//#include"Entity.h"
#include"SpriteSheetAnimation.h"

class Player //: public Entity
{
    public:
        Player();
        virtual ~Player();

        void LoadContent();//const char * entityName, std::pair<float, float> pos);
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev, InputManager input);//, InputManager input);
        void Draw(ALLEGRO_DISPLAY *display);

        void SetKarmaLevel(int newLevel);
        int  GetKarmaLevel();
        void SetMoney(int newAmount);
        int  GetMoney();
        std::pair<float, float> GetPosition();

    protected:
    private:
        ALLEGRO_BITMAP *playerImage;
        //float position[2];
        std::pair<float, float> position;
        std::pair<float, float> vel;
        float moveSpeed;
        float jumpspeed;
        float gravity;
        int cashAmount;
        int karmaLevel;

        bool activateGravity;

        enum Direction{DOWN, LEFT, RIGHT, UP};
        Direction direction ;

        Animation playerAnimation;
        //SpriteSheetAnimation spriteAnimation;// not needed
};

#endif // PLAYER_H
