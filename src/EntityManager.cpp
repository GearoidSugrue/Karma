#include "EntityManager.h"

EntityManager::EntityManager()
{
    //ctor
}

EntityManager::~EntityManager()
{
    //dtor
}

void EntityManager::LoadContent(const char* entityName)
{
    Entity *cat_Girl, *wallet_Guy, *cat, *lotto, *crane, *warningSign, *blocks;

    cat_Girl = new Entity();
    cat_Girl->LoadContent("entity_cat_girl.txt");
    wallet_Guy = new Entity();
    wallet_Guy->LoadContent("entity_wallet_guy.txt");
    cat = new Entity();
    cat->LoadContent("entity_cat.txt");
    lotto = new Entity();
    lotto->LoadContent("entity_lotto.txt");
    crane = new Entity();
    crane->LoadContent("entity_crane.txt");
    warningSign = new Entity();
    warningSign->LoadContent("entity_warning_sign.txt");
    blocks = new Entity();
    blocks->LoadContent("entity_blocks.txt");

    entities.push_back(cat_Girl);
    entities.push_back(wallet_Guy);
    entities.push_back(cat);
    entities.push_back(lotto);
    entities.push_back(crane);
    entities.push_back(warningSign);
    entities.push_back(blocks);
}

void EntityManager::UnloadContent()
{
    for(int i = 0; i < entities.size(); i++)
    {
        entities[i]->UnloadContent() ;
        delete entities[i];
    }
}

void EntityManager::Update(ALLEGRO_EVENT ev, InputManager input, Player* player)
{
    for(int i = 0; i < entities.size(); i++)
    {
        entities[i]->Update(ev, input, player) ;
    }
}

void EntityManager::Draw(ALLEGRO_DISPLAY *display)
{
     for(int i = 0; i < entities.size(); i++)
    {
        entities[i]->Draw(display);
    }
}
