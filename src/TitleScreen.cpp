#include "TitleScreen.h"


TitleScreen::TitleScreen()
{
    //ctor
}

TitleScreen::~TitleScreen()
{
    //dtor
}

void TitleScreen::LoadContent()
{
    font = al_load_font("slkscr.ttf", 28, NULL);
    logo = al_load_bitmap("Karma_Logo.png");
    std::cout<<"creating Titlescreen..."<<std::endl;
}

void TitleScreen::UnloadContent()
{
    al_destroy_font(font) ;
    al_destroy_bitmap(logo) ;
    std::cout<<"destroying TitleScreen..."<<std::endl;
}

void TitleScreen::Update(ALLEGRO_EVENT ev)
{
    if(input.IsKeyPressed(ev, ALLEGRO_KEY_BACKSPACE))
    {
        ScreenManager::GetInstance().AddScreen(new SplashScreen);
    }
    else if(input.IsKeyPressed(ev, ALLEGRO_KEY_ENTER))
    {
        ScreenManager::GetInstance().AddScreen(new GameplayScreen);
    }
}

void TitleScreen::Draw(ALLEGRO_DISPLAY *display)
{
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(logo, (al_get_display_width(display)/2) - (al_get_bitmap_width(logo)/2), (al_get_display_height(display)/5), NULL);
    al_draw_text(font, al_map_rgb(150, 150, 150), (al_get_display_width(display)/2) - 320, al_get_display_height(display)/1.5f, NULL, "Press 'Enter' to start or 'ESC' to quit.");
}
