#include "EntityManager.h"

EntityManager::EntityManager()
{
    //ctor
}

EntityManager::~EntityManager()
{
    //dtor
}

void EntityManager::LoadContent(const char* entityName)//change this
{
    Entity *cat_Girl, *wallet_Guy;

    cat_Girl = new Entity();
    cat_Girl->LoadContent("entity_cat_girl.txt");
    wallet_Guy = new Entity();
    wallet_Guy->LoadContent("entity_wallet_guy.txt");

    entities.push_back(cat_Girl);
    entities.push_back(wallet_Guy);

    for(int i = 0; i < entities.size(); i++)
    {

        //entities[i]->LoadContent() ;

    }
}

void EntityManager::UnloadContent()
{
    for(int i = 0; i < entities.size(); i++)
    {
        entities[i]->UnloadContent() ;
        delete entities[i];
    }
}

void EntityManager::Update(ALLEGRO_EVENT ev, InputManager input)
{
    for(int i = 0; i < entities.size(); i++)
    {
        entities[i]->Update(ev, input) ;
    }
}

void EntityManager::Draw(ALLEGRO_DISPLAY *display)
{
     for(int i = 0; i < entities.size(); i++)
    {
        entities[i]->Draw(display);
    }
}
 /*
void EntityManager::LoadEntity(const char *filename)
{
    std::ifstream openfile(filename) ;
    if(openfile.is_open())
    {
        std::string line, value ;
        int state = NULL;
        enum LoadState { POSITION, TEXT, YES, NO} ;

        while(!openfile.eof())
        {
            std::getline(openfile, line);

            if(line.find("[Position]") != std::string::npos)
            {
                state = POSITION;
                continue; //skips the rest of the loop and goes back to the top of the loop.
            }
            else if (line.find("[Text]") != std::string::npos)
            {
                state = TEXT;
                continue;
            }
            else if (line.find("[Yes]") != std::string::npos)
            {
                state = YES;
                continue;
            }
            else if (line.find("[No]") != std::string::npos)
            {
                state = NO;
                continue;
            }

            switch(state)
            {
            case POSITION:
                if(line.length() > 0)
                {
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                    {

                    }
                }

                    //ileSpriteSheet = al_load_bitmap(line.c_str());
                break;
            case TEXT:
                std::stringstream str (line);
                //std::vector<int> tempVector;

                //while(!str.eof())
                //{
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                        //tempVector.push_back(atoi(value.c_str()));
                //}
                //worldMap.push_back(tempVector);
                break;
            case YES:


                break;
            case NO:

                break;
            }

        //mapSizeY = loadCounterY ;
        }
       // return ary ;
    }
    else
    {

        std::cout<<"Failed to open map file."<<std::endl;
    }
}
*/
