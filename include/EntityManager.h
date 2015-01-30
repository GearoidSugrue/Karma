#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include"Entity.h"
#include"Player.h"

//#include"Player.h"
#include<vector>


class EntityManager
{
    public:
        EntityManager();
        virtual ~EntityManager();

        void LoadContent(const char* entityName);
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev, InputManager input, Player* player);
        void Draw(ALLEGRO_DISPLAY *display);

    std::vector< Entity* > entities;

    protected:
    private:
};

#endif // ENTITYMANAGER_H
