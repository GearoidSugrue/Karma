#ifndef ENTITY_H
#define ENTITY_H

#include<vector>
#include<string>
#include<allegro.h>
#include <allegro_primitives.h>
#include <sstream>
#include<iostream>
#include <fstream>

#include"InputManager.h"
#include"Animation.h"
//#include"EntityManager.h"

class Entity //: public EntityManager
{
    public:
        Entity();
        virtual ~Entity();

        void LoadContent(const char* entityName);//,  std::pair<float, float> pos);//change this
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev, InputManager inputManager);
        void Draw(ALLEGRO_DISPLAY *display);//should these be virtual

        void LoadEntity(const char *filename);

        std::pair<float, float> pos, prevPosition, velocity;
        Animation animation;
        bool activateGravity;
        //char *entityName;
        enum EntityType {CHARACTER, OBJECT};
        EntityType type;

    protected:

    ALLEGRO_BITMAP *image;
    //float gravity;

    private:
        std::string textBoxText ;
        std::string dialogText ;
        std::string yesText;
        std::string noText;
        std::string imageName;
        int sizeWidth;
        int sizeHeight;
        ALLEGRO_COLOR color;

};

#endif // ENTITY_H
