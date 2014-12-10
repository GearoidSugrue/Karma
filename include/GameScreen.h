#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include<allegro.h>
#include"InputManager.h"
#include <iostream>
#include <fstream>
#include <sstream>


class GameScreen
{
    public:
        GameScreen();
        virtual ~GameScreen();

        virtual void LoadContent();
        virtual void UnloadContent();
        virtual void Update(ALLEGRO_EVENT ev);
        virtual void Draw(ALLEGRO_DISPLAY *display);

        InputManager GetInput();

    protected:
        InputManager input;
        //std::vector< std::vector<std::string> > attributes;
        //std::vector< std::vector<std::string> > contents;

    private:
        void DrawMap(std::vector< std::vector<int> > &worldMap);
        void LoadMap(const char *filename, std::vector< std::vector<int> > &worldMap);
        void CameraUpdate(float* cameraPosition, float x, float y, int width, int height);

        std::vector< std::vector<int> > worldMap;
        ALLEGRO_BITMAP *tileSpriteSheet;
        const float BlockSize = 70;
        const int ScreenWidth = 1190 ;
        const int ScreenHeight = 700 ;

        //int mapSizeX;
        //int mapSizeY;

};

#endif // GAMESCREEN_H
