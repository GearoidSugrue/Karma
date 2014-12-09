#include "SplashScreen.h"
#include "ScreenManager.h"


SplashScreen::SplashScreen()
{
    //ctor
}

SplashScreen::~SplashScreen()
{
    //dtor
}

void SplashScreen::LoadContent()
{
    font = al_load_font("slkscr.ttf", 18, NULL);

}

void SplashScreen::UnloadContent()
{
    al_destroy_font(font) ;

}

void SplashScreen::Update(ALLEGRO_EVENT ev)
{
    if(input.IsKeyPressed(ev, ALLEGRO_KEY_SPACE))
    {
        ScreenManager::GetInstance().AddScreen(new TitleScreen);
    }
}

void SplashScreen::Draw(ALLEGRO_DISPLAY *display)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font, al_map_rgb(255, 255 ,255), 300, 400, NULL, "By: Gearoid Sugrue");
}





