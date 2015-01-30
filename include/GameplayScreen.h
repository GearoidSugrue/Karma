#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H

#include <sstream>
#include "GameScreen.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ScreenManager.h"
#include "EndScreen.h"

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

        void DrawMap();
        void LoadMap(const char *filename);
        void CameraUpdate(float x, float y, int width, int height);
        void DrawHUD(ALLEGRO_DISPLAY *display);
        int DrawWrappedText(ALLEGRO_FONT *af,char atext[1024],ALLEGRO_COLOR fc, int x1, int y1, int width, int flags,bool draw);

        bool IsNearEntity(Entity *ent);

        void EntitiesInteraction();

        std::vector< std::vector<int> > worldMap;

        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *tileSpriteSheet;
        const float BlockSize = 70;
        const int ScreenWidth = 1190 ;
        const int ScreenHeight = 700 ;
        bool isEndGame;
        char *HudText;
        ALLEGRO_TRANSFORM camera ;
        ALLEGRO_COLOR fontColor;
};

#endif // GAMEPLAYSCREEN_H
