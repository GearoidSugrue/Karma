#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H

//#include<allegro.h>
#include <sstream>
#include "GameScreen.h"//is this needed???
#include "Player.h"
#include "Entity.h"
#include "EntityManager.h"

class GameplayScreen : public GameScreen
{
    public:
        GameplayScreen();
        virtual ~GameplayScreen();

        void LoadContent();
        void UnloadContent();
        void Update(ALLEGRO_EVENT ev);
        void Draw(ALLEGRO_DISPLAY *display);


    protected:

    private:
        Player player;
        EntityManager entityMan;

        //Entity cat_girl;

        void DrawMap();
        void LoadMap(const char *filename);
        void CameraUpdate(float x, float y, int width, int height);
        void DrawHUD(ALLEGRO_DISPLAY *display);
        int DrawWrappedText(ALLEGRO_FONT *af,char atext[1024],ALLEGRO_COLOR fc, int x1, int y1, int width, int flags,bool draw);

        bool IsNearEntity(float entX, float entY, int entWidth, int entHeight);

        void EntitiesInteraction();
        void EntitiesDraw();

        std::vector< std::vector<int> > worldMap;
        //std::vector<Entity*> entities;

        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *tileSpriteSheet;
        const float BlockSize = 70;
        const int ScreenWidth = 1190 ;
        const int ScreenHeight = 700 ;

        //std::pair<float, float> cameraPosition;
        char *dialogText;
        ALLEGRO_TRANSFORM camera ;




};

#endif // GAMEPLAYSCREEN_H
