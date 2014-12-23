#include "GameScreen.h"

GameScreen::GameScreen()
{
    //ctor
}

GameScreen::~GameScreen()
{
    //dtor
}

void GameScreen::LoadContent()
{

    LoadMap("Map1.txt", worldMap);
    std::cout<<"creating Gamescreen..."<<std::endl;

}

void GameScreen::UnloadContent()
{
    //attributes.clear();
    //contents.clear();


    worldMap.clear();
    std::vector< std::vector<int> >(worldMap).swap(worldMap);
    al_destroy_bitmap(tileSpriteSheet);

    //BlockSize = NULL;
}

void GameScreen::Update(ALLEGRO_EVENT ev)
{

    if(input.IsKeyPressed(ev, ALLEGRO_KEY_LEFT))//move player character...move these ifs?
    {
        //Update player's velocity

    }
    else if(input.IsKeyPressed(ev, ALLEGRO_KEY_RIGHT))
    {

    }
    else if(input.IsKeyPressed(ev, ALLEGRO_KEY_UP))
    {


    }
    else if(input.IsKeyPressed(ev, ALLEGRO_KEY_SPACE))
    {
        //action command.
    }
    //std::cout << "Is this doing anything..." <<std::endl ;

}


void GameScreen::Draw(ALLEGRO_DISPLAY *display)
{
    DrawMap(worldMap);
}

InputManager GameScreen::GetInput()
{
    return input;
}


void GameScreen::DrawMap(std::vector< std::vector<int> > &worldMap)//int worldMap[])
{
    int value ;

    for(int i = 0; i < worldMap.size(); i++)
    {
        for(int j = 0; j < worldMap[i].size(); j++)
        {
            //if(worldMap[i][j] != 0)
                al_draw_bitmap_region(tileSpriteSheet, worldMap[i][j] * BlockSize, 0,
                    BlockSize, BlockSize, j * BlockSize, i * BlockSize, NULL);
        }
    }
}

void GameScreen::LoadMap(const char *filename, std::vector< std::vector<int> > &worldMap)
{
    std::ifstream openfile(filename) ;
    if(openfile.is_open())
    {
        std::string line, value ;
        int state = NULL;
        enum LoadState { TileSet, Map} ;

        while(!openfile.eof())
        {
            std::getline(openfile, line);

            if(line.find("[TileSet]") != std::string::npos)
            {
                state = TileSet;
                continue; //skips the rest of the loop and goes back to the top of the loop.
            }
            else if (line.find("[Map]") != std::string::npos)
            {
                state = Map;
                continue;
            }

            switch(state)
            {
            case TileSet:
                if(line.length() > 0)
                    tileSpriteSheet = al_load_bitmap(line.c_str());
                break;
            case Map:
                std::stringstream str (line);
                std::vector<int> tempVector;

                while(!str.eof())
                {
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                        tempVector.push_back(atoi(value.c_str()));
                }
                worldMap.push_back(tempVector);
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

void GameScreen::CameraUpdate(float* cameraPosition, float x, float y, int width, int height)
{
    cameraPosition[0] = -(ScreenWidth / 2) + (x + width / 2);
    cameraPosition[1] = -(ScreenWidth / 2) + (y + height / 2);

    if(cameraPosition[0] < 0)
    {
        cameraPosition[0] = 0 ;
    }
    if(cameraPosition[1] < 0)
    {
        cameraPosition[1] = 0 ;
    }

}


