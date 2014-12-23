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
    std::cout<<"creating Splashscreen..."<<std::endl;
}

void SplashScreen::UnloadContent()
{
    al_destroy_font(font) ;
    std::cout<<"destroying Splashscreen..."<<std::endl;

    //GameScreen::UnloadContent();
}

void SplashScreen::Update(ALLEGRO_EVENT ev)
{
    //fanimation.Update();
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        ScreenManager::GetInstance().AddScreen(new TitleScreen);
    }
    //al_get_keyboard_state(&keyState);
    //if(input.IsKeyPressed(ev, ALLEGRO_KEY_SPACE))
    //if(input.IsKeyPressed(ev, ALLEGRO_KEY_SPACE))
    //{
    //}
}

void SplashScreen::Draw(ALLEGRO_DISPLAY *display)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font, al_map_rgb(255, 255 ,255), al_get_display_width(display)/2 - 100, al_get_display_height(display)/2, NULL, "By: Gearoid Sugrue");
    //al_draw_text(font, al_map_rgb(150, 150, 150), (al_get_display_width(display)/2) - 320, al_get_display_height(display)/1.5f, NULL, "Press 'Enter' to start or 'ESC' to quit.");

}





