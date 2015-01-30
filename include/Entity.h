#ifndef ENTITY_H
#define ENTITY_H

#include<vector>
#include<string>
#include<allegro.h>
#include <allegro_primitives.h>
#include <sstream>
#include<iostream>
#include <fstream>
#include <cstring>

#include"InputManager.h"
#include"Animation.h"
#include"SpriteSheetAnimation.h"
#include"Player.h"

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        void LoadContent(const char* entityN);
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev, InputManager inputManager, Player* player);
        void Draw(ALLEGRO_DISPLAY *display);

        void LoadEntity(const char *filename);

        std::pair<float, float> pos, velocity;
        bool activateGravity, isActionComplete, isNear;

        enum EntityType {CHARACTER, OBJECT};
        EntityType type;

        int sizeWidth;
        int sizeHeight;


        const char * entityName;
        char * textBoxText ;
        char * dialogText ;
        char * yesText;
        char * noText;

        std::string imageName;
        ALLEGRO_COLOR color;
        SpriteSheetAnimation spriteAni;
        Animation animation;

    protected:

    private:

        void YesAction();
        void NoAction();
        ALLEGRO_BITMAP *image;

        int frame;
        int timer;
};

#endif // ENTITY_H
